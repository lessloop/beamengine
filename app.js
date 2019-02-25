/*
  Aerostat Beam Engine - Redis-backed highly-scale-able and cloud-fit media beam engine.
  Copyright (C) 2019  Streampunk Media Ltd.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.

  https://www.streampunk.media/ mailto:furnace@streampunk.media
  14 Ormiscaig, Aultbea, Achnasheen, IV22 2JJ  U.K.
*/

const Koa = require('koa');
const Router = require('koa-router');
// const Bull = require('bull');
// const producer = new Bull('my-first-queue');
const config = require('./config.json');
const routes = require('./lib/routes.js');
const Boom = require('boom');

const app = new Koa();
const router = new Router();

router
  .get('/beams', routes.beamsRoute)
  .get('/beams/:fmtSpec', routes.formatRoute)
  .get('/beams/:fmtSpec/:streamSpec', routes.streamRoute)
  .get('/beams/:fmtSpec/:streamSpec/start', routes.startRedirect)
  .get('/beams/:fmtSpec/:streamSpec/packet_:pts(-?\\d+)(\\.json)?', routes.packetRoute)
  .get('/beams/:fmtSpec/:streamSpec/frame_:pts(-?\\d+)(\\.json)?', routes.frameRoute)
  .get('/beams/:fmtSpec/:streamSpec/:mediaSpec', routes.mediaRoute)
  .get('/beams/:fmtSpec/:streamSpec/:mediaSpec/:dataSpec', routes.dataRoute)
  .post('/beams', routes.createBeam)
  .put('/beams/:fmtSpec', routes.formatUpdate)
  .post('/beams/:fmtSpec', routes.createRelated)
  .put('/beams/:fmtSpec/:streamSpec/:mediaSpec', routes.mediaUpdate)
  .put('/beams/:fmtSpec/:streamSpec/:mediaSpec/:dataSpec', routes.dataUpdate);

app
  .use(async (ctx, next) => {
    try {
      await next();
      if (ctx.status === 404) {
        ctx.body = { statusCode: 404, error: 'Not Found',
          message: 'Resource not found.' };
      }
    } catch (err) {
      if (Boom.isBoom(err)) {
        ctx.response.headers = err.output.headers;
        ctx.body = err.output.payload;
        ctx.status = err.output.statusCode;
      } else {
        ctx.status = 500;
        ctx.body = { statusCode: ctx.status, error: 'Internal Server Error',
          message: err.message };
      }
      console.error(err.stack);
    }
  })
  .use(router.routes())
  .use(router.allowedMethods());

if (!module.parent) {
  app.listen(config.app.port);
}

app.on('error', (err) => {
  console.log(err.stack);
});

module.exports = app;
