/*
  Aerostat Beam Engine - Redis-backed highly-scale-able and cloud-fit media beam engine.
  Copyright (C) 2018  Streampunk Media Ltd.

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

#ifndef ENCODE_H
#define ENCODE_H

#include "beamcoder_util.h"
#include <vector>

extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavutil/pixdesc.h>
  #include <libavformat/avformat.h>
}

void encoderExecute(napi_env env, void* data);
void encoderComplete(napi_env env, napi_status asyncStatus, void* data);
napi_value encoder(napi_env env, napi_callback_info info);

void encodeExecute(napi_env env, void* data);
void encodeComplete(napi_env env, napi_status asyncStatus, void* data);
napi_value encode(napi_env env, napi_callback_info info);

void encoderFinalizer(napi_env env, void* data, void* hint);

struct encoderCarrier : carrier {
  AVCodecContext* encoder;
  char* codecName;
  size_t codecNameLen = 0;
  ~encoderCarrier() {
    if (encoder != nullptr) {
      avcodec_close(encoder);
      avcodec_free_context(&encoder);
    }
}
};

struct encodeCarrier : carrier {
  AVCodecContext* encoder;
  std::vector<AVFrame*> frames;
  std::vector<AVPacket*> packets;
  ~encodeCarrier() { }
};

#endif ENCODE_H
