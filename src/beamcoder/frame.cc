/*
  Aerostat Beam Coder - Node.JS native mappings for FFmpeg.
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

#include "frame.h"

napi_value getFrameLinesize(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value array, element;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_array(env, &array);
  CHECK_STATUS;

  for ( int x = 0 ; x < AV_NUM_DATA_POINTERS ; x++ ) {
    if (f->frame->linesize[x] == 0) break;
    status = napi_create_int32(env, f->frame->linesize[x], &element);
    CHECK_STATUS;
    status = napi_set_element(env, array, x, element);
    CHECK_STATUS;
  }

  return array;
}

napi_value setFrameLinesize(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result, element;
  napi_valuetype type;
  frameData* f;
  bool isArray;
  uint32_t lineCount;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame linesize must be provided with a value.");
  }
  status = napi_is_array(env, args[0], &isArray);
  CHECK_STATUS;
  if (!isArray) {
    NAPI_THROW_ERROR("Set frame linesize must use an array of numbers.");
  }

  status = napi_get_array_length(env, args[0], &lineCount);
  CHECK_STATUS;
  for ( uint32_t x = 0 ; x < lineCount ; x++ ) {
    status = napi_get_element(env, args[0], x, &element);
    CHECK_STATUS;
    status = napi_typeof(env, element, &type);
    CHECK_STATUS;
    if (type != napi_number) {
      NAPI_THROW_ERROR("Set frame linesize must use an array of numbers.");
    }
  }

  for ( uint32_t x = 0 ; x < AV_NUM_DATA_POINTERS ; x++ ) {
    if (x >= lineCount) {
      f->frame->linesize[x] = 0;
      continue;
    }
    status = napi_get_element(env, args[0], x, &element);
    CHECK_STATUS;
    status = napi_get_value_int32(env, element, &f->frame->linesize[x]);
    CHECK_STATUS;
  }

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameWidth(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->width, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameWidth(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame width must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame width property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->width);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameHeight(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->height, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameHeight(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame height must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame height property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->height);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameNbSamples(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->nb_samples, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameNbSamples(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame nb_samples must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame nb_samples property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->nb_samples);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameFormat(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;
  const char* name = nullptr;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  // Assume audio data using FFmpeg's own technique
  if (f->frame->nb_samples > 0 && (f->frame->channel_layout || f->frame->channels > 0)) {
    name = av_get_sample_fmt_name((AVSampleFormat) f->frame->format);
  }
  if (name == nullptr) { // Assume that it is video data
    name = av_get_pix_fmt_name((AVPixelFormat) f->frame->format);
  }
  if (name == nullptr) {
    status = napi_get_null(env, &result);
  } else {
    status = napi_create_string_utf8(env, (char*) name, NAPI_AUTO_LENGTH, &result);
  }
  CHECK_STATUS;

  return result;
}

napi_value setFrameFormat(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;
  int format = (int) AV_PIX_FMT_NONE;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame format must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type == napi_null) {
    f->frame->format = -1;
    goto done;
  }
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame format property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  // TODO this may give surprising results
  format = (int) av_get_pix_fmt( name);
  if (format == AV_PIX_FMT_NONE) {
    format = (int) av_get_sample_fmt((const char*) name);
    if ((format != AV_SAMPLE_FMT_NONE) && (f->frame->nb_samples == 0)) {
      f->frame->nb_samples = 1; // Cludge ... found a sample format ... force audio mode
      f->frame->channels = 1;
    }
  }

  f->frame->format = format;

done:
  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameKeyFrame(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_get_boolean(env, (f->frame->key_frame == 1), &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameKeyFrame(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  bool keyFrame;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame key_frame must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_boolean) {
    NAPI_THROW_ERROR("Frame key_frame property must be set with a Boolean.");
  }
  status = napi_get_value_bool(env, args[0], &keyFrame);
  CHECK_STATUS;
  f->frame->key_frame = (keyFrame) ? 1 : 0;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePictType(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;
  const char* name;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  switch (f->frame->pict_type) {
    case AV_PICTURE_TYPE_I:
      name = "I";
      break;
    case AV_PICTURE_TYPE_P:
      name = "P";
      break;
    case AV_PICTURE_TYPE_B:
      name = "B";
      break;
    case AV_PICTURE_TYPE_S:
      name = "S";
      break;
    case AV_PICTURE_TYPE_SI:
      name = "SI";
      break;
    case AV_PICTURE_TYPE_SP:
      name = "SP";
      break;
    case AV_PICTURE_TYPE_BI:
      name = "BI";
      break;
    default:
      name = nullptr;
      break;
  }

  if (name == nullptr) {
    status = napi_get_undefined(env, &result);
  } else {
    status = napi_create_string_utf8(env, name, NAPI_AUTO_LENGTH, &result);
  }
  CHECK_STATUS;
  return result;
}

napi_value setFramePictType(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame pict_type must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if ((type == napi_undefined) || (type == napi_null)) {
    f->frame->pict_type = AV_PICTURE_TYPE_NONE;
    goto done;
  }
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame pict_type property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  switch (name[0]) {
    case 'I':
      f->frame->pict_type = AV_PICTURE_TYPE_I;
      break;
    case 'P':
      f->frame->pict_type = AV_PICTURE_TYPE_P;
      break;
    case 'B':
      f->frame->pict_type = (len == 1) ? AV_PICTURE_TYPE_B : AV_PICTURE_TYPE_BI;
      break;
    case 'S':
      if (len == 1) {
        f->frame->pict_type = AV_PICTURE_TYPE_S;
        break;
      }
      if (len == 2) {
        if (name[1] == 'I') {
          f->frame->pict_type = AV_PICTURE_TYPE_SI;
          break;
        }
        if (name[1] == 'P') {
          f->frame->pict_type = AV_PICTURE_TYPE_SP;
          break;
        }
      }
      f->frame->pict_type = AV_PICTURE_TYPE_NONE;
      break;
    default:
      f->frame->pict_type = AV_PICTURE_TYPE_NONE;
      break;
  }

done:
  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameSampleAR(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result, element;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_array(env, &result);
  CHECK_STATUS;
  status = napi_create_int32(env, f->frame->sample_aspect_ratio.num, &element);
  CHECK_STATUS;
  status = napi_set_element(env, result, 0, element);
  CHECK_STATUS;
  status = napi_create_int32(env, f->frame->sample_aspect_ratio.den, &element);
  CHECK_STATUS;
  status = napi_set_element(env, result, 1, element);
  CHECK_STATUS;

  return result;
}

napi_value setFrameSampleAR(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result, element;
  napi_valuetype type;
  frameData* f;
  bool isArray;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame sample_aspect_ratio must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if ((type == napi_undefined) || (type == napi_null)) {
    f->frame->sample_aspect_ratio = { 0, 1 };
    goto done;
  }
  status = napi_is_array(env, args[0], &isArray);
  CHECK_STATUS;
  if (!isArray) {
    NAPI_THROW_ERROR("Frame sample_aspect_ratio property must be set with an array of two numbers.");
  }

  f->frame->sample_aspect_ratio = { 0, 1 };
  status = napi_get_element(env, args[0], 0, &element);
  CHECK_STATUS;
  status = napi_get_value_int32(env, element, &f->frame->sample_aspect_ratio.num);
  CHECK_STATUS;
  status = napi_get_element(env, args[0], 1, &element);
  CHECK_STATUS;
  status = napi_get_value_int32(env, element, &f->frame->sample_aspect_ratio.den);
  CHECK_STATUS;

done:
  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePTS(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int64(env, f->frame->pts, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFramePTS(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame PTS must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame PTS property must be set with a number.");
  }
  status = napi_get_value_int64(env, args[0], &f->frame->pts);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePktDTS(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int64(env, f->frame->pkt_dts, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFramePktDTS(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame pkt_dts must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame pkt_dts property must be set with a number.");
  }
  status = napi_get_value_int64(env, args[0], &f->frame->pkt_dts);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameCodecPicNum(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->coded_picture_number, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameCodecPicNum(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame coded_picture_number must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame coded_picture_number property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->coded_picture_number);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameDispPicNum(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->display_picture_number, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameDispPicNum(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame display_picture_number must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame display_picture_number property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->display_picture_number);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameQuality(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->quality, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameQuality(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame quality must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame quality property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->quality);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameRepeatPict(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->repeat_pict, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameRepeatPict(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame repeat_pict must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame repeat_pict property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->repeat_pict);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameInterlaced(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_get_boolean(env, f->frame->interlaced_frame == 1, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameInterlaced(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  bool interlaced;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame interlaced_frame must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_boolean) {
    NAPI_THROW_ERROR("Frame interlaced_frame property must be set with a Boolean.");
  }
  status = napi_get_value_bool(env, args[0], &interlaced);
  CHECK_STATUS;
  f->frame->interlaced_frame = (interlaced) ? 1 : 0;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameTopFieldFirst(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_get_boolean(env, f->frame->top_field_first == 1, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameTopFieldFirst(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  bool topFieldFirst;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame top_field_first must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_boolean) {
    NAPI_THROW_ERROR("Frame top_field_first property must be set with a Boolean.");
  }
  status = napi_get_value_bool(env, args[0], &topFieldFirst);
  CHECK_STATUS;
  f->frame->top_field_first = (topFieldFirst) ? 1 : 0;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePalHasChanged(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_get_boolean(env, f->frame->palette_has_changed == 1, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFramePalHasChanged(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  bool palHasChanged;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame palette_has_changed must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_boolean) {
    NAPI_THROW_ERROR("Frame palette_has_changed property must be set with a Boolean.");
  }
  status = napi_get_value_bool(env, args[0], &palHasChanged);
  CHECK_STATUS;
  f->frame->palette_has_changed = (palHasChanged) ? 1 : 0;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameReorderOpq(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int64(env, f->frame->reordered_opaque, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameReorderOpq(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame reordered_opaque must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame reordered_opaque property must be set with a number.");
  }
  status = napi_get_value_int64(env, args[0], &f->frame->reordered_opaque);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameSampleRate(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->sample_rate, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameSampleRate(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame sample_rate must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame sample_rate property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], &f->frame->sample_rate);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameChanLayout(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  char channelLayoutName[64];
  av_get_channel_layout_string(channelLayoutName, 64, -1, f->frame->channel_layout);

  status = napi_create_string_utf8(env, channelLayoutName, NAPI_AUTO_LENGTH, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameChanLayout(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame channel_layout must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame channel_layout property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  f->frame->channel_layout = av_get_channel_layout(name);
  free(name);

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameData(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value array, element;
  frameData* f;
  AVBufferRef* hintRef;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  if (f->frame->buf == nullptr) {
    status = napi_get_null(env, &array);
  } else {
    status = napi_create_array(env, &array);
    CHECK_STATUS;
    for ( int x = 0 ; x < AV_NUM_DATA_POINTERS ; x++ ) {
    //  printf("Buffer %i is %p\n", x, f->frame->buf[x]);
      if (f->frame->buf[x] == nullptr) continue;
      hintRef = av_buffer_ref(f->frame->buf[x]);
      status = napi_create_external_buffer(env, hintRef->size, hintRef->data,
        frameBufferFinalizer, hintRef, &element);
      CHECK_STATUS;
      status = napi_set_element(env, array, x, element);
      CHECK_STATUS;
    }
  }

  CHECK_STATUS;
  return array;
}

napi_value setFrameData(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result, element;
  bool isArray, isBuffer;
  frameData* f;
  uint8_t* data;
  size_t length;
  avBufRef* avr;
  uint32_t bufCount;
  napi_ref dataRef;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set packet data must be provided with an array of buffer values.");
  }
  status = napi_is_array(env, args[0], &isArray);
  CHECK_STATUS;
  if (!isArray) {
    NAPI_THROW_ERROR("Packet data property must be set with an array of buffer values.");
  }
  status = napi_get_array_length(env, args[0], &bufCount);
  CHECK_STATUS;
  for ( uint32_t x = 0 ; x < bufCount ; x++ ) {
    status = napi_get_element(env, args[0], x, &element);
    CHECK_STATUS;
    status = napi_is_buffer(env, element, &isBuffer);
    CHECK_STATUS;
    if (!isBuffer) {
      NAPI_THROW_ERROR("All elements of the packet data array must be buffers.");
    }
  }

  for ( auto it = f->dataRefs.cbegin() ; it != f->dataRefs.cend() ; it++ ) {
    // printf("On new buffers provided, freeing data refs for pts = %i\n", f->frame->pts);
    status = napi_delete_reference(env, *it);
    CHECK_STATUS;
  }
  f->dataRefs.clear();
  for ( uint32_t x = 0 ; x < AV_NUM_DATA_POINTERS ; x++) {
    if (f->frame->buf[x] != nullptr) {
      av_buffer_unref(&f->frame->buf[x]);
    }
  }
  for ( uint32_t x = 0 ; x < AV_NUM_DATA_POINTERS ; x++) {
    if (x >= bufCount) {
      if (f->frame->buf[x] != nullptr) {
        av_buffer_unref(&f->frame->buf[x]);
      }
      f->frame->buf[x] = nullptr;
      f->frame->data[x] = nullptr;
      continue;
    }
    status = napi_get_element(env, args[0], x, &element);
    CHECK_STATUS;
    // printf("Creating data reference for pts = %i\n", f->frame->pts);
    status = napi_create_reference(env, element, 1, &dataRef);
    CHECK_STATUS;
    f->dataRefs.push_back(dataRef);
    avr = new avBufRef;
    avr->pts = f->frame->pts;
    // printf("Creating AV reference for pts = %i\n", f->frame->pts);
    status = napi_create_reference(env, element, 1, &avr->ref);
    CHECK_STATUS;
    avr->env = env;
    status = napi_get_buffer_info(env, element, (void**) &data, &length);
    CHECK_STATUS;

    f->frame->buf[x] = av_buffer_create(data, length, frameBufferFree, avr, 0);
    CHECK_STATUS;
    f->frame->data[x] = f->frame->buf[x]->data;
  }

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameFlags(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_object(env, &result);
  CHECK_STATUS;
  status = beam_set_bool(env, result, "CORRUPT", (f->frame->flags & AV_FRAME_FLAG_CORRUPT) != 0);
  CHECK_STATUS;
  status = beam_set_bool(env, result, "DISCARD", (f->frame->flags & AV_FRAME_FLAG_DISCARD) != 0);
  CHECK_STATUS;

  return result;
}

napi_value setFrameFlags(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  bool present, flag;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame flags must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_object) {
    NAPI_THROW_ERROR("Frame flags property must be set with an object of Boolean flags.");
  }
  status = beam_get_bool(env, args[0], "CORRUPT", &present, &flag);
  CHECK_STATUS;
  if (present) { f->frame->flags = (flag) ?
    f->frame->flags | AV_FRAME_FLAG_CORRUPT :
    f->frame->flags & ~AV_FRAME_FLAG_CORRUPT; }
  status = beam_get_bool(env, args[0], "DISCARD", &present, &flag);
  CHECK_STATUS;
  if (present) { f->frame->flags = (flag) ?
    f->frame->flags | AV_FRAME_FLAG_DISCARD :
    f->frame->flags & ~AV_FRAME_FLAG_DISCARD; }

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameColorRange(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_string_utf8(env, (char*) av_color_range_name(f->frame->color_range),
    NAPI_AUTO_LENGTH, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameColorRange(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;
  int ret;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame color_range must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame color_range property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  ret = av_color_range_from_name(name);
  free(name);
  if (ret < 0) {
    NAPI_THROW_ERROR("Color range was not recognised. Try one of 'tv' (MPEG), 'pc' (JPEG) or 'unknown'.");
  }
  f->frame->color_range = (AVColorRange) ret;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameColorPrimaries(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_string_utf8(env,
    (char*) av_color_primaries_name(f->frame->color_primaries),
    NAPI_AUTO_LENGTH, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameColorPrimaries(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;
  int ret;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame color_primaries must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame color_primaries property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  ret = av_color_primaries_from_name(name);
  free(name);
  if (ret < 0) {
    NAPI_THROW_ERROR("Color primaries not recognised. Did you mean e.g. 'bt709'?");
  }
  f->frame->color_primaries = (AVColorPrimaries) ret;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameColorTrc(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_string_utf8(env,
    (char*) av_color_transfer_name(f->frame->color_trc),
    NAPI_AUTO_LENGTH, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameColorTrc(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;
  int ret;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame color_trc must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame color_trc property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  ret = av_color_transfer_from_name(name);
  free(name);
  if (ret < 0) {
    NAPI_THROW_ERROR("Color transfer characteristic not recognised. Did you mean e.g. 'bt709'?");
  }
  f->frame->color_trc = (AVColorTransferCharacteristic) ret;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameColorspace(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_string_utf8(env,
    (char*) av_color_space_name(f->frame->colorspace),
    NAPI_AUTO_LENGTH, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameColorspace(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;
  int ret;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame colorspace must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame colorspace property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  ret = av_color_space_from_name(name);
  free(name);
  if (ret < 0) {
    NAPI_THROW_ERROR("Colorspace not recognised. Did you mean e.g. 'bt709'?");
  }
  f->frame->colorspace = (AVColorSpace) ret;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameChromaLoc(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_string_utf8(env,
    (char*) av_chroma_location_name(f->frame->chroma_location),
    NAPI_AUTO_LENGTH, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameChromaLoc(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  char* name;
  size_t len;
  int ret;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame chroma_location must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_string) {
    NAPI_THROW_ERROR("Frame chroma_location property must be set with a string.");
  }
  status = napi_get_value_string_utf8(env, args[0], nullptr, 0, &len);
  CHECK_STATUS;
  name = (char*) malloc(sizeof(char) * (len + 1));
  status = napi_get_value_string_utf8(env, args[0], name, len + 1, &len);
  CHECK_STATUS;

  ret = av_chroma_location_from_name(name);
  free(name);
  if (ret < 0) {
    NAPI_THROW_ERROR("Chroma location not recognised.");
  }
  f->frame->chroma_location = (AVChromaLocation) ret;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameBestEffortTS(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int64(env, f->frame->best_effort_timestamp, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameBestEffortTS(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame best_effort_timestamp must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame best_effort_timestamp property must be set with a number.");
  }
  status = napi_get_value_int64(env, args[0], &f->frame->best_effort_timestamp);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePktPos(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int64(env, f->frame->pkt_pos, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFramePktPos(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame pkt_pos must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame pkt_pos property must be set with a number.");
  }
  status = napi_get_value_int64(env, args[0], &f->frame->pkt_pos);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePktDuration(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int64(env, f->frame->pkt_duration, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFramePktDuration(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame pkt_duration must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame pkt_duration property must be set with a number.");
  }
  status = napi_get_value_int64(env, args[0], &f->frame->pkt_duration);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameMetadata(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;
  AVDictionaryEntry* tag = nullptr;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  if (f->frame->metadata != nullptr) {
    status = napi_create_object(env, &result);
    CHECK_STATUS;
    while((tag = av_dict_get(f->frame->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
      status = beam_set_string_utf8(env, result, tag->key, tag->value);
      CHECK_STATUS;
    }
  } else {
    status = napi_get_null(env, &result);
    CHECK_STATUS;
  }

  return result;
}

napi_value setFrameMetadata(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result, names, name, nValue;
  napi_valuetype type;
  frameData* f;
  uint32_t nameCount;
  AVDictionary* dict = nullptr;
  char * key, * value;
  size_t strLen;
  int ret;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set metadata must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type == napi_null || type == napi_undefined) {
    f->frame->metadata = nullptr;
    goto done;
  }
  if (type != napi_object) {
    NAPI_THROW_ERROR("Frame metadata property must be set with a object.");
  }

  status = napi_get_property_names(env, args[0], &names);
  CHECK_STATUS;
  status = napi_get_array_length(env, names, &nameCount);
  CHECK_STATUS;
  for ( uint32_t x = 0 ; x < nameCount ; x++ ) {
    status = napi_get_element(env, names, x, &name);
    CHECK_STATUS;
    status = napi_get_value_string_utf8(env, name, nullptr, 0, &strLen);
    CHECK_STATUS;
    key = (char*) malloc(sizeof(char) * (strLen + 1));
    status = napi_get_value_string_utf8(env, name, key, strLen + 1, &strLen);
    CHECK_STATUS;

    status = napi_get_property(env, args[0], name, &nValue);
    CHECK_STATUS;
    status = napi_coerce_to_string(env, nValue, &nValue);
    CHECK_STATUS;
    status = napi_get_value_string_utf8(env, nValue, nullptr, 0, &strLen);
    CHECK_STATUS;
    value = (char*) malloc(sizeof(char) * (strLen + 1));
    status = napi_get_value_string_utf8(env, nValue, value, strLen + 1, &strLen);
    CHECK_STATUS;

    ret = av_dict_set(&dict, (const char *) key, (const char *) value, 0);
    if (ret < 0) {
      printf("DEBUG: Error setting metadata value on a frame.");
    }
  }

  f->frame->metadata = dict;
done:
  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameDecodeErrFlags(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_object(env, &result);
  CHECK_STATUS;

  status = beam_set_bool(env, result, "INVALID_BITSTREAM",
    (f->frame->decode_error_flags & FF_DECODE_ERROR_INVALID_BITSTREAM) != 0);
  CHECK_STATUS;
  status = beam_set_bool(env, result, "MISSING_REFERENCE",
    (f->frame->decode_error_flags & FF_DECODE_ERROR_MISSING_REFERENCE) != 0);
  CHECK_STATUS;

  return result;
}

napi_value setFrameDecodeErrFlags(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;
  bool present, flag;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set decode_error_flags must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_object) {
    NAPI_THROW_ERROR("Frame decode_error_flags property must be set with a object of Boolean-valued properties.");
  }

  status = beam_get_bool(env, args[0], "INVALID_BITSTREAM", &present, &flag);
  CHECK_STATUS;
  if (present) { f->frame->decode_error_flags = (flag) ?
    f->frame->decode_error_flags | FF_DECODE_ERROR_INVALID_BITSTREAM :
    f->frame->decode_error_flags & ~FF_DECODE_ERROR_INVALID_BITSTREAM; }
  status = beam_get_bool(env, args[0], "MISSING_REFERENCE", &present, &flag);
  CHECK_STATUS;
  if (present) { f->frame->decode_error_flags = (flag) ?
    f->frame->decode_error_flags | FF_DECODE_ERROR_INVALID_BITSTREAM :
    f->frame->decode_error_flags & ~FF_DECODE_ERROR_MISSING_REFERENCE; }

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameChannels(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->channels, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameChannels(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame channels must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame channels property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], (int32_t*) &f->frame->channels);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFramePktSize(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->pkt_size, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFramePktSize(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame pkt_size must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame pkt_size property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], (int32_t*) &f->frame->pkt_size);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameCropTop(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->crop_top, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameCropTop(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame crop_top must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame crop_top property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], (int32_t*) &f->frame->crop_top);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameCropBottom(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->crop_bottom, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameCropBottom(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame crop_bottom must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame crop_bottom property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], (int32_t*) &f->frame->crop_bottom);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameCropLeft(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->crop_left, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameCropLeft(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame crop_left must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame crop_left property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], (int32_t*) &f->frame->crop_left);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value getFrameCropRight(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  frameData* f;

  status = napi_get_cb_info(env, info, 0, nullptr, nullptr, (void**) &f);
  CHECK_STATUS;

  status = napi_create_int32(env, f->frame->crop_right, &result);
  CHECK_STATUS;
  return result;
}

napi_value setFrameCropRight(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;
  napi_valuetype type;
  frameData* f;

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, (void**) &f);
  CHECK_STATUS;
  if (argc < 1) {
    NAPI_THROW_ERROR("Set frame crop_right must be provided with a value.");
  }
  status = napi_typeof(env, args[0], &type);
  CHECK_STATUS;
  if (type != napi_number) {
    NAPI_THROW_ERROR("Frame crop_right property must be set with a number.");
  }
  status = napi_get_value_int32(env, args[0], (int32_t*) &f->frame->crop_right);
  CHECK_STATUS;

  status = napi_get_undefined(env, &result);
  CHECK_STATUS;
  return result;
}

napi_value makeFrame(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result, global, jsObject, assign;
  napi_valuetype type;
  bool isArray;
  frameData* f = new frameData;
  f->frame = av_frame_alloc();
  int align = 32; // av_cpu_max_align();

  size_t argc = 1;
  napi_value args[1];

  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  CHECK_STATUS;
  if (argc > 1) {
    NAPI_THROW_ERROR("Frame may be created with zero or one options object argument.");
  }
  if (argc == 1) {
    status = napi_typeof(env, args[0], &type);
    CHECK_STATUS;
    status = napi_is_array(env, args[0], &isArray);
    CHECK_STATUS;
    if (isArray || (type != napi_object)) {
      NAPI_THROW_ERROR("Cannot create a frame without an options object.");
    }
  }

  status = frameFromAVFrame(env, f, &result);
  CHECK_STATUS;

  if (argc == 1) {
    status = napi_get_global(env, &global);
    CHECK_STATUS;
    status = napi_get_named_property(env, global, "Object", &jsObject);
    CHECK_STATUS;
    status = napi_get_named_property(env, jsObject, "assign", &assign);
    CHECK_STATUS;
    const napi_value fargs[] = { result, args[0] };
    status = napi_call_function(env, result, assign, 2, fargs, &result);
    CHECK_STATUS;
  }

  // MAINTAIN: needs to track FFmpeg
  if (f->frame->format >= 0) { // set up some useful line sizes.
    if (f->frame->width > 0 && f->frame->height > 0) { // video
      const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get((AVPixelFormat) f->frame->format);
      int ret, i;
      if (!desc)
      NAPI_THROW_ERROR("Could not determine frame descriptor details.");

      if (!f->frame->linesize[0]) {
        for( i = 1 ; i <= align ; i += i) {
          ret = av_image_fill_linesizes(f->frame->linesize, (AVPixelFormat) f->frame->format,
                                            FFALIGN(f->frame->width, i));
          if (ret < 0)
            NAPI_THROW_ERROR("Failed to calculate line sizes.");
          if (!(f->frame->linesize[0] & (align-1)))
            break;
        }
        for ( i = 0 ; i < 4 && f->frame->linesize[i] ; i++) {
          f->frame->linesize[i] = FFALIGN(f->frame->linesize[i], align);
        }
      }
    }
    else if (f->frame->nb_samples > 0 && (f->frame->channel_layout || f->frame->channels > 0)) {
      int channels;
      int planar = av_sample_fmt_is_planar((AVSampleFormat) f->frame->format);
      int planes;
      int ret;

      if (!f->frame->channels)
        f->frame->channels = av_get_channel_layout_nb_channels(f->frame->channel_layout);

      channels = f->frame->channels;
      planes = planar ? channels : 1;

      // TODO: is this needed? CHECK_CHANNELS_CONSISTENCY(f->frame);
      if (!f->frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&f->frame->linesize[0], channels,
                                         f->frame->nb_samples, (AVSampleFormat) f->frame->format,
                                         align);
        if (ret < 0)
          NAPI_THROW_ERROR("Unable to determine frame line size.");
      }
    }
  } // Format provided

  return result;
}

napi_status frameFromAVFrame(napi_env env, frameData* f, napi_value* result) {
  napi_status status;
  napi_value jsFrame, extFrame, typeName;
  int64_t externalMemory;

  status = napi_create_object(env, &jsFrame);
  PASS_STATUS;
  status = napi_create_string_utf8(env, "Frame", NAPI_AUTO_LENGTH, &typeName);
  PASS_STATUS;
  status = napi_create_external(env, f, frameDataFinalizer, nullptr, &extFrame);
  PASS_STATUS;

  napi_property_descriptor desc[] = {
    { "type", nullptr, nullptr, nullptr, nullptr, typeName, napi_enumerable, nullptr },
    { "linesize", nullptr, nullptr, getFrameLinesize, setFrameLinesize, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "width", nullptr, nullptr, getFrameWidth, setFrameWidth, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "height", nullptr, nullptr, getFrameHeight, setFrameHeight, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "nb_samples", nullptr, nullptr, getFrameNbSamples, setFrameNbSamples, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "format", nullptr, nullptr, getFrameFormat, setFrameFormat, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "key_frame", nullptr, nullptr, getFrameKeyFrame, setFrameKeyFrame, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "pict_type", nullptr, nullptr, getFramePictType, setFramePictType, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "sample_aspect_ratio", nullptr, nullptr, getFrameSampleAR, setFrameSampleAR, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "pts", nullptr, nullptr, getFramePTS, setFramePTS, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f }, // 10
    { "pkt_dts", nullptr, nullptr, getFramePktDTS, setFramePktDTS, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "codec_picture_number", nullptr, nullptr, getFrameCodecPicNum, setFrameCodecPicNum, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "display_picture_number", nullptr, nullptr, getFrameDispPicNum, setFrameDispPicNum, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "quality", nullptr, nullptr, getFrameQuality, setFrameQuality, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "repeat_pict", nullptr, nullptr, getFrameRepeatPict, setFrameRepeatPict, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "interlaced_frame", nullptr, nullptr, getFrameInterlaced, setFrameInterlaced, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "top_field_first", nullptr, nullptr, getFrameTopFieldFirst, setFrameTopFieldFirst, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "palette_has_changed", nullptr, nullptr, getFramePalHasChanged, setFramePalHasChanged, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "reordered_opaque", nullptr, nullptr, getFrameReorderOpq, setFrameReorderOpq, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "sample_rate", nullptr, nullptr, getFrameSampleRate, setFrameSampleRate, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f }, // 20
    { "channel_layout", nullptr, nullptr, getFrameChanLayout, setFrameChanLayout, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "data", nullptr, nullptr, getFrameData, setFrameData, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "flags", nullptr, nullptr, getFrameFlags, setFrameFlags, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "color_range", nullptr, nullptr, getFrameColorRange, setFrameColorRange, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "color_primaries", nullptr, nullptr, getFrameColorPrimaries, setFrameColorPrimaries, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "color_trc", nullptr, nullptr, getFrameColorTrc, setFrameColorTrc, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "colorspace", nullptr, nullptr, getFrameColorspace, setFrameColorspace, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "chroma_location", nullptr, nullptr, getFrameChromaLoc, setFrameChromaLoc, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "best_effort_timestamp", nullptr, nullptr, getFrameBestEffortTS, setFrameBestEffortTS, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "pkt_pos", nullptr, nullptr, getFramePktPos, setFramePktPos, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f }, // 30
    { "pkt_duration", nullptr, nullptr, getFramePktDuration, setFramePktDuration, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "metadata", nullptr, nullptr, getFrameMetadata, setFrameMetadata, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "decode_error_flags", nullptr, nullptr, getFrameDecodeErrFlags, setFrameDecodeErrFlags, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "channels", nullptr, nullptr, getFrameChannels, setFrameChannels, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "pkt_size", nullptr, nullptr, getFramePktSize, setFramePktSize, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "crop_top", nullptr, nullptr, getFrameCropTop, setFrameCropTop, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "crop_bottom", nullptr, nullptr, getFrameCropBottom, setFrameCropBottom, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "crop_left", nullptr, nullptr, getFrameCropLeft, setFrameCropLeft, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "crop_right", nullptr, nullptr, getFrameCropRight, setFrameCropRight, nullptr,
      (napi_property_attributes) (napi_writable | napi_enumerable), f },
    { "_frame", nullptr, nullptr, nullptr, nullptr, extFrame, napi_default, nullptr } // 40
  };
  status = napi_define_properties(env, jsFrame, 40, desc);
  PASS_STATUS;

  for ( int x = 0 ; x < AV_NUM_DATA_POINTERS ; x++ ) {
    if (f->frame->buf[x] == nullptr) break;
    f->extSize += f->frame->buf[x]->size;
  }
  status = napi_adjust_external_memory(env, f->extSize, &externalMemory);
  PASS_STATUS;

  *result = jsFrame;
  return napi_ok;
}

void frameFinalizer(napi_env env, void* data, void* hint) {
  AVFrame* frame = (AVFrame*) data;
  av_frame_free(&frame);
  // printf("Freeing a frame.\n");
}

void frameDataFinalizer(napi_env env, void* data, void* hint) {
  napi_status status;
  int64_t externalMemory;
  frameData* f = (frameData*) data;
  // printf("Freeing frame data for pts = %i\n", f->frame->pts);
  status = napi_adjust_external_memory(env, -f->extSize, &externalMemory);
  if (status != napi_ok) {
    printf("DEBUG: Failed to adjust external memory downwards on frame delete.\n");
  }
  for ( auto it = f->dataRefs.cbegin() ; it != f->dataRefs.cend() ; it++) {
    // printf("Freeing data reference for frame with pts = %i\n", f->frame->pts);
    status = napi_delete_reference(env, *it);
    if (status != napi_ok) {
      printf("DEBUG: Failed to delete data reference for frame data, status %i.\n", status);
    }
  }
  delete f;
}

void frameBufferFinalizer(napi_env env, void* data, void* hint) {
  AVBufferRef* hintRef = (AVBufferRef*) hint;
  av_buffer_unref(&hintRef);
  // printf("Unreffing an AV buffer.\n");
}

void frameBufferFree(void* opaque, uint8_t* data) {
  napi_status status;
  avBufRef* avr = (avBufRef*) opaque;
  // printf("AV freeing a frame buffer. pts = %i\n", avr->pts);
  status = napi_delete_reference(avr->env, (napi_ref) avr->ref);
  if (status != napi_ok)
    printf("DEBUG: Failed to delete buffer reference associated with an AVBufferRef.");
  delete avr;
}
