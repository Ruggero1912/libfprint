/*
 * Validity VFS0090 driver for libfprint
 * Copyright (C) 2017 Nikita Mikhailov <nikita.s.mikhailov@gmail.com>
 * Copyright (C) 2018-2019 Marco Trevisan <marco@ubuntu.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#pragma once

#include "fpi-device.h"

G_DECLARE_FINAL_TYPE (FpiDeviceVfs0090, fpi_device_vfs0090, FPI, DEVICE_VFS0090, FpDevice)

GType fpi_tod_shared_driver_get_type (void);

#define DMI_PRODUCT_NAME_NODE "/sys/class/dmi/id/product_name"
#define DMI_PRODUCT_SERIAL_NODE "/sys/class/dmi/id/product_serial"

#define VFS_USB_TIMEOUT 3000
#define VFS_USB_INTERRUPT_TIMEOUT 0
#define VFS_USB_BUFFER_SIZE 30 * 1024
#define VFS_USB_INTERRUPT_BUFFER_SIZE 0x100

#define VFS_MASTER_KEY_SIZE 0x20
#define VFS_PUBLIC_KEY_SIZE 0x40
#define VFS_ECDSA_PRIVATE_KEY_SIZE 0x60
#define VFS_ECDSA_SIGNATURE_SIZE 0x48
#define VFS_IMAGE_SIZE 144
#define VFS_IMAGE_RESCALE 2
#define VFS_BZ3_THRESHOLD 12

enum INIT_STATES {
  INIT_STATE_GENERATE_MAIN_SEED,
  INIT_STATE_SEQ_1,
  INIT_STATE_SEQ_2,
  INIT_STATE_SEQ_3,
  INIT_STATE_SEQ_4,
  INIT_STATE_SEQ_5,
  INIT_STATE_SEQ_6,
  INIT_STATE_MASTER_KEY,
  INIT_STATE_ECDSA_KEY,
  INIT_STATE_TLS_CERT,
  INIT_STATE_PUBLIC_KEY,
  INIT_STATE_HANDSHAKE,

  INIT_STATE_LAST
};

/* This is the init state in which we check whether the chip is initialized */
#define PROBE_STATE_LAST INIT_STATE_SEQ_2 + 1

enum TLS_HANDSHAKE_STATES {
  TLS_HANDSHAKE_STATE_CLIENT_HELLO,
  TLS_HANDSHAKE_STATE_SERVER_HELLO_RCV,
  TLS_HANDSHAKE_GENERATE_CERT,
  TLS_HANDSHAKE_STATE_SEND_CERT,
  TLS_HANDSHAKE_STATE_CERT_REPLY,

  TLS_HANDSHAKE_STATE_LAST
};

enum ACTIVATE_STATES {
  ACTIVATE_STATE_CHECK_DB,
  ACTIVATE_STATE_CHECK_DB_DONE,
  ACTIVATE_STATE_GREEN_LED_ON,
  ACTIVATE_STATE_SEQ_1,
  ACTIVATE_STATE_SEQ_2,
  ACTIVATE_STATE_SEQ_3,
  ACTIVATE_STATE_SEQ_4,
  ACTIVATE_STATE_SEQ_5,
  ACTIVATE_STATE_SEQ_6,
  ACTIVATE_STATE_SEQ_7,
  ACTIVATE_STATE_SCAN_MATRIX,
  ACTIVATE_STATE_WAIT_DEVICE,

  ACTIVATE_STATE_LAST
};

/* Keep this in Sync with VFS_SCAN_INTERRUPTS */
enum SCAN_STATES {
  SCAN_STATE_WAITING_FOR_FINGER,
  SCAN_STATE_FINGER_ON_SENSOR,
  SCAN_STATE_IN_PROGRESS,
  SCAN_STATE_FAILED_TOO_SHORT,
  SCAN_STATE_FAILED_TOO_FAST,
  SCAN_STATE_COMPLETED,
  SCAN_STATE_SUCCESS,
  SCAN_STATE_SUCCESS_LOW_QUALITY,
  SCAN_STATE_DB_MATCH_RESULT_WAIT,
  SCAN_STATE_DB_MATCH_FAILED,
  SCAN_STATE_DB_MATCH_SUCCESS,

  SCAN_STATE_LAST
};

/* Keep in sync with SCAN_STATES */
enum VFS_SCAN_INTERRUPTS {
  VFS_SCAN_WAITING_FOR_FINGER = SCAN_STATE_WAITING_FOR_FINGER,
  VFS_SCAN_FINGER_ON_SENSOR,
  VFS_SCAN_IN_PROGRESS,
  VFS_SCAN_FAILED_TOO_SHORT,
  VFS_SCAN_FAILED_TOO_FAST,
  VFS_SCAN_COMPLETED,
  VFS_SCAN_SUCCESS,
  VFS_SCAN_SUCCESS_LOW_QUALITY,
  VFS_SCAN_DB_MATCH_FAILED,
  VFS_SCAN_DB_MATCH_SUCCESS,

  VFS_SCAN_UNKNOWN = 100,
};

/* Move downnn */
enum DB_CHECK_STATES {
  DB_CHECK_STATE_REQUEST,
  DB_CHECK_STATE_MATCH_RESULT_WAIT,

  DB_CHECK_STATE_MATCH_FAILED = VFS_SCAN_DB_MATCH_FAILED,
  DB_CHECK_STATE_MATCH_SUCCESS = VFS_SCAN_DB_MATCH_SUCCESS,
  DB_CHECK_STATE_MATCH_SUCCESS_DETAILS,

  DB_CHECK_STATE_MATCH_CHECK_RESULT,
  DB_CHECK_STATE_GREEN_LED_BLINK,
  DB_CHECK_STATE_AFTER_GREEN_LED_BLINK,
  DB_CHECK_STATE_RED_LED_BLINK,
  DB_CHECK_STATE_AFTER_RED_LED_BLINK,
  DB_CHECK_STATE_SUBMIT_RESULT,

  DB_CHECK_STATE_LAST
};

enum SCAN_ERROR_STATES {
  SCAN_ERROR_STATE_LED_BLINK,
  SCAN_ERROR_STATE_REACTIVATE_REQUEST,

  SCAN_ERROR_STATE_LAST
};

enum IMAGE_DOWNLOAD_STATES {
  IMAGE_DOWNLOAD_STATE_1,
  IMAGE_DOWNLOAD_STATE_2,
  IMAGE_DOWNLOAD_STATE_3,
  IMAGE_DOWNLOAD_STATE_SUBMIT_IMAGE,
  IMAGE_DOWNLOAD_STATE_CHECK_RESULT,
  IMAGE_DOWNLOAD_STATE_GREEN_LED_BLINK,
  IMAGE_DOWNLOAD_STATE_AFTER_GREEN_LED_BLINK,
  IMAGE_DOWNLOAD_STATE_RED_LED_BLINK,
  IMAGE_DOWNLOAD_STATE_AFTER_RED_LED_BLINK,
  IMAGE_DOWNLOAD_STATE_SUBMIT_RESULT,

  IMAGE_DOWNLOAD_STATE_LAST
};

enum DEACTIVATE_STATES {
  DEACTIVATE_STOP_TRANSFER,
  DEACTIVATE_STATE_SEQ_1,
  DEACTIVATE_STATE_LED_OFF,

  DEACTIVATE_STATE_LAST
};

enum REACTIVATE_STATES {
  REACTIVATE_STATE_WAIT,
  REACTIVATE_STATE_DEACTIVATE,
  REACTIVATE_STATE_ACTIVATE,
  REACTIVATE_STATE_SCAN,

  REACTIVATE_STATE_LAST
};

enum DATA_EXCHANGE_MODE {
  DATA_EXCHANGE_PLAIN,
  DATA_EXCHANGE_ENCRYPTED,
};

typedef struct _VfsDataExchange
{
  gboolean             weak_match;
  const unsigned char *msg;
  int                  msg_length;
  const unsigned char *rsp;
  int                  rsp_length;
} VfsDataExchange;

typedef struct __attribute__((__packed__))
{
  guint16 status;
} VfsReply;

typedef struct __attribute__((__packed__))
{
  VfsReply msg;
  guint32 data_size;
  unsigned char image_data[VFS_IMAGE_SIZE];
} Vfs0090ImageChunk;

typedef struct __attribute__((__packed__))
{
  VfsReply msg;
  guint32 data_size;
  guint16 width;
  guint16 height;
  guint16 unknown;
  struct __attribute__((__packed__))
  {
    guint16 bit_per_pixels;
    guint32 error;
    unsigned char image_data[VFS_IMAGE_SIZE];
  } image;
} Vfs0090ImageReply;

typedef struct __attribute__((__packed__))
{
  guint8 request_id;
  const guint8 unknowns1[2];
  guint16 storage_id;
  guint16 user_id;
  guint16 unknowns2[3];
} VfsDbIdentifyQuery;

typedef struct __attribute__((__packed__))
{
  guint16 reply_id;
  guint16 finger_id;
  guint8 db;
} VfsDbIdentifyInterrupt;

const unsigned char TEST_SEED[] = "VirtualBox\0" "0";

static const unsigned char INIT_SEQUENCE_MSG1[] = { 0x01 };

static const unsigned char INIT_SEQUENCE_MSG2[] = { 0x19 };

static const unsigned char INIT_SEQUENCE_MSG3[] = { 0x43, 0x02 };

static const unsigned char INIT_SEQUENCE_MSG4[] = {
  0x06, 0x02, 0x00, 0x00, 0x01, 0x39, 0x17, 0xb3,
  0xdd, 0xa9, 0x13, 0x83, 0xb5, 0xbc, 0xac, 0x64,
  0xfa, 0x4a, 0xd3, 0x5d, 0xce, 0x96, 0x57, 0x0a,
  0x9d, 0x2d, 0x97, 0x4b, 0x80, 0x92, 0x6a, 0x43,
  0x1f, 0x9c, 0xd4, 0x62, 0x48, 0x98, 0x0a, 0x26,
  0x3c, 0x6f, 0xce, 0xf6, 0xa8, 0x28, 0x39, 0xa9,
  0x0b, 0x59, 0xac, 0x59, 0x08, 0x48, 0x85, 0x9a,
  0xfa, 0xc8, 0x17, 0xb7, 0xd5, 0x3b, 0xf5, 0x1c,
  0xd3, 0x20, 0x5c, 0x1b, 0x8f, 0x43, 0x04, 0x8b,
  0xe8, 0x25, 0x3c, 0x3b, 0xd2, 0x47, 0x93, 0x7c,
  0x83, 0x7a, 0xca, 0x8b, 0x18, 0xd3, 0xcc, 0x8e,
  0xe8, 0xc8, 0x97, 0x1a, 0xc4, 0xf6, 0x88, 0x81,
  0x3c, 0xf3, 0xd8, 0x55, 0x0d, 0x71, 0x49, 0x69,
  0x85, 0xb7, 0xec, 0x07, 0xff, 0x2d, 0xc7, 0x89,
  0x6d, 0x33, 0x0f, 0xda, 0xb2, 0x63, 0xa0, 0xee,
  0x43, 0x3a, 0x5c, 0x4b, 0xc9, 0x10, 0x43, 0x9d,
  0x1c, 0x61, 0x61, 0x85, 0x3f, 0xeb, 0x03, 0xf5,
  0x50, 0x22, 0x09, 0x50, 0x2e, 0x73, 0x08, 0xbe,
  0xb7, 0x91, 0x94, 0x73, 0xcf, 0xe6, 0x9f, 0x42,
  0x2c, 0x30, 0x50, 0x2d, 0x22, 0x6a, 0x4d, 0x0a,
  0x34, 0xd9, 0x6c, 0x8c, 0x77, 0x95, 0x6c, 0xf6,
  0x9d, 0xb8, 0xef, 0x6c, 0xf9, 0x27, 0xa3, 0xb5,
  0x78, 0x49, 0xd4, 0xaa, 0x8a, 0xd4, 0xb4, 0x42,
  0x66, 0x92, 0x3e, 0x34, 0xb8, 0x2a, 0x39, 0xc8,
  0x14, 0x6b, 0xa3, 0xcd, 0x70, 0x8c, 0x70, 0xdf,
  0xed, 0xb5, 0x0c, 0x2d, 0xe6, 0x1f, 0xeb, 0x45,
  0xb1, 0xd4, 0xf1, 0x95, 0x84, 0x29, 0x72, 0x03,
  0xf5, 0xfd, 0xc8, 0x65, 0x79, 0x5f, 0xec, 0x9d,
  0x64, 0x49, 0xf3, 0xba, 0x9b, 0x6f, 0x1e, 0x4b,
  0xed, 0x69, 0x8e, 0xe1, 0x51, 0xe8, 0x3d, 0x4d,
  0x87, 0x02, 0xf7, 0x6a, 0x40, 0x06, 0xcf, 0xa2,
  0x4d, 0x9b, 0x79, 0x78, 0x88, 0x20, 0x3b, 0x22,
  0x69, 0xf8, 0xa7, 0x7d, 0x52, 0x40, 0x34, 0xac,
  0x32, 0xe4, 0xaf, 0x58, 0xb8, 0x6e, 0xbc, 0x63,
  0x55, 0x2c, 0xb3, 0x5b, 0x12, 0xb2, 0x85, 0x25,
  0x5d, 0xea, 0xf3, 0xa3, 0x2b, 0xf4, 0x6c, 0xdc,
  0x5a, 0xd3, 0xbc, 0x1c, 0x9e, 0xd1, 0xbc, 0xc1,
  0x12, 0xc7, 0x21, 0x43, 0xf9, 0xae, 0xc5, 0x68,
  0xe2, 0xca, 0xcf, 0xa8, 0x9b, 0xa0, 0xc7, 0xbb,
  0x65, 0x59, 0x0d, 0x8b, 0x93, 0xe6, 0x87, 0x1a,
  0x33, 0xc6, 0xc6, 0x98, 0x3c, 0x0a, 0xcd, 0x04,
  0xe7, 0x37, 0xff, 0x55, 0xee, 0xe0, 0x24, 0xca,
  0x6b, 0x9a, 0x48, 0x33, 0x2c, 0x1a, 0x69, 0xa5,
  0xa3, 0xfd, 0xd2, 0x4b, 0x96, 0x4c, 0xf7, 0xe7,
  0xc5, 0x52, 0x29, 0xbb, 0x0b, 0x48, 0xa6, 0xe3,
  0x39, 0xeb, 0x2c, 0x42, 0xd0, 0x7e, 0xc8, 0x50,
  0xa4, 0xee, 0x78, 0x06, 0x60, 0xad, 0x6c, 0x77,
  0xff, 0xa3, 0x02, 0xa6, 0x3b, 0xd1, 0x94, 0x26,
  0x13, 0x4c, 0x45, 0x33, 0xd6, 0xf9, 0x67, 0x44,
  0x11, 0x63, 0xfb, 0x78, 0xb7, 0x35, 0x47, 0xc6,
  0x8a, 0x49, 0x3b, 0x2f, 0x80, 0x0d, 0x3c, 0xda,
  0xb8, 0x27, 0xb1, 0x16, 0x76, 0x27, 0x89, 0x99,
  0x2a, 0xae, 0x3c, 0x8a, 0xb3, 0x45, 0xa4, 0x9e,
  0xdd, 0x31, 0x2d, 0xfd, 0x2a, 0x27, 0xbc, 0x50,
  0x14, 0x27, 0xdc, 0x7f, 0xa0, 0x0a, 0xc3, 0xc5,
  0xc3, 0x65, 0x51, 0xdb, 0xb3, 0xd5, 0xca, 0xd8,
  0xd5, 0xbd, 0x7c, 0xea, 0x37, 0xe5, 0x8a, 0x31,
  0x30, 0x7a, 0x6d, 0x50, 0xe6, 0xae, 0x37, 0x9a,
  0x53, 0xf1, 0x36, 0x66, 0x78, 0xc0, 0x74, 0x1a,
  0x3d, 0x87, 0x2b, 0x8d, 0xcf, 0xef, 0xa7, 0xf6,
  0x31, 0x28, 0xdc, 0x82, 0x45
};

static const unsigned char INIT_SEQUENCE_MSG5[] = { 0x3e };

static const unsigned char INIT_SEQUENCE_RSP5[] = {
  0x00, 0x00, 0xef, 0x00, 0x40, 0x00, 0x00, 0x10,
  0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x05, 0x00,
  0x01, 0x04, 0x07, 0x00, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x10, 0x00, 0x00, 0x02, 0x01, 0x02, 0x00,
  0x00, 0x20, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00,
  0x05, 0x05, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00,
  0x00, 0x80, 0x00, 0x00, 0x06, 0x06, 0x03, 0x00,
  0x00, 0x80, 0x04, 0x00, 0x00, 0x80, 0x00, 0x00,
  0x04, 0x03, 0x05, 0x00, 0x00, 0x00, 0x05, 0x00,
  0x00, 0x00, 0x03, 0x00
};

static const unsigned char INIT_SEQUENCE_MSG6[] = {
  0x40, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x00
};

static const VfsDataExchange INIT_SEQUENCES[] = {
  {
    .msg = INIT_SEQUENCE_MSG1,
    .msg_length = G_N_ELEMENTS (INIT_SEQUENCE_MSG1),
    .rsp = NULL,
    .rsp_length = -1 /* 38 normally */,
  },
  {
    .msg = INIT_SEQUENCE_MSG2,
    .msg_length = G_N_ELEMENTS (INIT_SEQUENCE_MSG2),
    .rsp = NULL,
    .rsp_length = 68,
  },
  {
    .msg = INIT_SEQUENCE_MSG3,
    .msg_length = G_N_ELEMENTS (INIT_SEQUENCE_MSG3),
    .rsp = NULL,
    .rsp_length = 108,
  },
  {
    .msg = INIT_SEQUENCE_MSG4,
    .msg_length = G_N_ELEMENTS (INIT_SEQUENCE_MSG4),
    .rsp = NULL,
    .rsp_length = 2,
  },
  {
    .msg = INIT_SEQUENCE_MSG5,
    .msg_length = G_N_ELEMENTS (INIT_SEQUENCE_MSG5),
    .rsp = INIT_SEQUENCE_RSP5,
    .rsp_length = G_N_ELEMENTS (INIT_SEQUENCE_RSP5),
  },
  {
    .msg = INIT_SEQUENCE_MSG6,
    .msg_length = G_N_ELEMENTS (INIT_SEQUENCE_MSG6),
    .rsp = NULL,
    .rsp_length = -1,
  },
};

static const unsigned char PRE_KEY[] = {
  0x71, 0x7c, 0xd7, 0x2d, 0x09, 0x62, 0xbc, 0x4a,
  0x28, 0x46, 0x13, 0x8d, 0xbb, 0x2c, 0x24, 0x19,
  0x25, 0x12, 0xa7, 0x64, 0x07, 0x06, 0x5f, 0x38,
  0x38, 0x46, 0x13, 0x9d, 0x4b, 0xec, 0x20, 0x33,
};

static const unsigned char TLS_CERTIFICATE_BASE[] = {
  0x44, 0x00, 0x00, 0x00,
  0x16, 0x03, 0x03, 0x01, 0x55,

  0x0b, 0x00, 0x00,
  0xc0, 0x00, 0x00, 0xb8, 0x00, 0x00, 0xb8,

  0x00, 0x00,

  /* cert from pre-tls */
  0x17, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
  0x00, 0xab, 0x9d, 0xfd, 0xba, 0x74, 0x25, 0x29,
  0x93, 0x9d, 0x2d, 0x5d, 0xf4, 0x77, 0xec, 0x90,
  0x2e, 0x13, 0xb8, 0x21, 0x1a, 0x19, 0x70, 0x1e,
  0x50, 0x2f, 0xf5, 0x6e, 0x6e, 0x25, 0xae, 0x8c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xf4, 0x04,
  0x74, 0xf0, 0x7a, 0xe4, 0xe0, 0x79, 0xd1, 0xf1,
  0x9f, 0xae, 0xbd, 0xa8, 0xef, 0x1e, 0xfa, 0x18,
  0xc2, 0x6a, 0x76, 0xae, 0xa5, 0xaa, 0xbf, 0xc3,
  0x4f, 0x12, 0x94, 0x8c, 0x8f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xa5, 0x58, 0xed, 0x0f, 0x31, 0x33, 0x45,
  0x63, 0xc8, 0x8a, 0xd5, 0x53, 0xd9, 0xe4, 0x6e,
  0x20, 0x5d, 0x54, 0x3b, 0x83, 0x99, 0xcf, 0x9b,
  0xef, 0x9e, 0xa8, 0xaa, 0xc5, 0xeb, 0xfb, 0x21,
  0xa3,

  0x10, 0x00, 0x00, 0x41, 0x04, 0x1d, 0xd8,
  0x36, 0x68, 0xe9, 0xb0, 0x7b, 0x93, 0x12, 0x38,
  0x31, 0x23, 0x90, 0xc8, 0x87, 0xca, 0xdb, 0x82,
  0x27, 0x39, 0xde, 0x7b, 0x43, 0xd2, 0x23, 0xd7,
  0xcd, 0xd1, 0x3c, 0x77, 0x0e, 0xd2, 0xd1, 0x93,
  0x70, 0x02, 0xaf, 0x3b, 0x18, 0x47, 0xc5, 0x30,
  0x4c, 0x33, 0x60, 0xcf, 0xbf, 0xc5, 0x9b, 0x3c,
  0x67, 0xd9, 0x45, 0x06, 0x38, 0xda, 0x92, 0xbe,
  0x65, 0xbf, 0x81, 0x8c, 0xaa, 0x7e, 0x0f, 0x00,
  0x00, 0x48, 0x30, 0x46, 0x02, 0x21, 0x00, 0xa3,
  0xad, 0xaa, 0x61, 0x00, 0xe6, 0x9d, 0xbd, 0xcf,
  0x48, 0x73, 0xb7, 0xa6, 0xed, 0xe3, 0x62, 0x0a,
  0x79, 0xe4, 0xf8, 0x14, 0x27, 0x4d, 0xeb, 0x73,
  0x91, 0x01, 0x0c, 0xae, 0x08, 0xb9, 0x43, 0x02,
  0x21, 0x00, 0xd3, 0x28, 0xa4, 0x86, 0xcf, 0x8b,
  0xaf, 0x35, 0xc9, 0x04, 0xf7, 0x1f, 0xe2, 0x56,
  0x22, 0xf7, 0x5d, 0xdf, 0x53, 0x13, 0x4f, 0xc6,
  0xdb, 0x6b, 0xc0, 0x0d, 0x57, 0x90, 0xc4, 0x23,
  0xfe, 0x06, 0x14, 0x03, 0x03, 0x00, 0x01, 0x01,


  /* encrypted handshake */
  0x16, 0x03, 0x03, 0x00, 0x50,

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  0x6f, 0xda, 0xdb,
  0xa0, 0x35, 0x1b, 0xe1, 0xb9, 0xca, 0xa3, 0x90,
  0xdf, 0x7e, 0x17, 0xec, 0x0b, 0xe8, 0xcc, 0xf9,
  0xa4, 0x92, 0x1b, 0x77, 0x9c, 0x0f, 0xf3, 0xc6,
  0xdc, 0xf9, 0xb3, 0x7d, 0x3c, 0x41, 0x6c, 0x4c,
  0x80, 0x95, 0x66, 0x7e, 0xb1, 0x7e, 0x37, 0x3d,
  0x28, 0xef, 0xa4, 0xca, 0xfd, 0x3e, 0xfd, 0x8f,
  0xdd, 0x84, 0x10, 0xc5, 0xb2, 0x71, 0x38, 0xab,
  0x8d, 0x9c, 0xe3, 0xac, 0x46
};

static const unsigned char TLS_CLIENT_HELLO[] = {
  0x44, 0x00, 0x00, 0x00,
  0x16, 0x03, 0x03, 0x00, 0x43, 0x01, 0x00, 0x00,
  0x3f, 0x03, 0x03, 0x95, 0x6c, 0x41, 0xa9, 0x12,
  0x86, 0x8a, 0xda, 0x9b, 0xb2, 0x5b, 0xb4, 0xbb,
  0xd6, 0x1d, 0xde, 0x4f, 0xda, 0x23, 0x2a, 0x74,
  0x7b, 0x2a, 0x93, 0xf8, 0xac, 0xc6, 0x69, 0x24,
  0x70, 0xc4, 0x2a, 0x07, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0xc0, 0x05, 0x00,
  0x3d, 0x00, 0x00, 0x0a, 0x00, 0x04, 0x00, 0x02,
  0x00, 0x17, 0x00, 0x0b, 0x00, 0x02, 0x01, 0x00
};

static const unsigned char PRIVKEY[] = {
  0x1d, 0xd8, 0x36, 0x68, 0xe9, 0xb0, 0x7b, 0x93,
  0x12, 0x38, 0x31, 0x23, 0x90, 0xc8, 0x87, 0xca,
  0xdb, 0x82, 0x27, 0x39, 0xde, 0x7b, 0x43, 0xd2,
  0x23, 0xd7, 0xcd, 0xd1, 0x3c, 0x77, 0x0e, 0xd2,

  0xd1, 0x93, 0x70, 0x02, 0xaf, 0x3b, 0x18, 0x47,
  0xc5, 0x30, 0x4c, 0x33, 0x60, 0xcf, 0xbf, 0xc5,
  0x9b, 0x3c, 0x67, 0xd9, 0x45, 0x06, 0x38, 0xda,
  0x92, 0xbe, 0x65, 0xbf, 0x81, 0x8c, 0xaa, 0x7e,

  0x20, 0x14, 0x3b, 0x7b, 0x62, 0x64, 0x90, 0x07,
  0x54, 0x4e, 0x7a, 0x98, 0xf9, 0x81, 0xbe, 0xc1,
  0xf2, 0x1f, 0x9a, 0x29, 0x65, 0xb6, 0xcc, 0x29,
  0x0c, 0x45, 0xd3, 0x87, 0xae, 0xbf, 0xa4, 0xd9
};

static const unsigned char ACTIVATE_SEQUENCE_MSG1[] = {
  0x08, 0x5c, 0x20, 0x00, 0x80, 0x07, 0x00, 0x00,
  0x00, 0x04
};

static const unsigned char ACTIVATE_SEQUENCE_MSG2[] = {
  0x07, 0x80, 0x20, 0x00, 0x80, 0x04
};

static const unsigned char ACTIVATE_SEQUENCE_MSG345[] = {
  0x75
};
static const unsigned char ACTIVATE_SEQUENCE_RSP345[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
  0x71, 0x00                             /* 0x01 */
};

static const unsigned char ACTIVATE_SEQUENCE_MSG67[] = {
  0x43, 0x02
};

unsigned char SCAN_MATRIX[] = {
  0x02, 0x98, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00,
  0x00, 0x20, 0x00, 0x08, 0x00, 0x00, 0x20, 0x00,
  0x80, 0x00, 0x00, 0x01, 0x00, 0x32, 0x00, 0x70,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x20, 0x20, 0x05,
  0x00, 0x24, 0x20, 0x00, 0x00, 0x50, 0x20, 0x77,
  0x36, 0x28, 0x20, 0x01, 0x00, 0x30, 0x20, 0x01,
  0x00, 0x08, 0x21, 0x70, 0x00, 0x0c, 0x21, 0x00,
  0x00, 0x48, 0x21, 0x02, 0x00, 0x4c, 0x21, 0x00,
  0x00, 0x58, 0x20, 0x00, 0x00, 0x5c, 0x20, 0x00,
  0x00, 0x60, 0x20, 0x00, 0x00, 0x68, 0x20, 0x05,
  0x00, 0x6c, 0x20, 0x01, 0x29, 0x70, 0x20, 0x01,
  0x21, 0x74, 0x20, 0x01, 0x88, 0x78, 0x20, 0x01,
  0x80, 0x84, 0x20, 0x20, 0x00, 0x94, 0x20, 0x01,
  0x80, 0x9c, 0x20, 0x09, 0x02, 0xa0, 0x20, 0x0b,
  0x19, 0xb4, 0x20, 0x00, 0x00, 0xb8, 0x20, 0x3b,
  0x04, 0xbc, 0x20, 0x14, 0x00, 0xc0, 0x20, 0x02,
  0x00, 0xc4, 0x20, 0x01, 0x00, 0xc8, 0x20, 0x02,
  0x00, 0x33, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x80, 0xcc, 0x20, 0x00, 0x00, 0xf5, 0x03, 0xd0,
  0x20, 0x00, 0x00, 0xa1, 0x01, 0x32, 0x00, 0x44,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xdc, 0x20, 0xe8,
  0x03, 0xe0, 0x20, 0x64, 0x01, 0xe4, 0x20, 0xd0,
  0x02, 0xe8, 0x20, 0x00, 0x01, 0xf0, 0x20, 0x05,
  0x00, 0xf8, 0x20, 0x05, 0x00, 0xfc, 0x20, 0x00,
  0x00, 0xb8, 0x20, 0x3b, 0x00, 0x00, 0x08, 0x04,
  0x00, 0x14, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00,
  0x00, 0x08, 0x08, 0x00, 0x00, 0x14, 0x08, 0x30,
  0x00, 0x08, 0x08, 0x00, 0x00, 0x14, 0x08, 0x31,
  0x00, 0x1c, 0x08, 0x1a, 0x00, 0x32, 0x00, 0x0c,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x50, 0x11, 0x01,
  0x00, 0x4c, 0x11, 0x26, 0x00, 0x34, 0x00, 0x08,
  0x03, 0x10, 0x07, 0x1d, 0x10, 0x07, 0x1d, 0x10,
  0x07, 0x1d, 0x10, 0x07, 0x1d, 0x10, 0x07, 0x1c,
  0x01, 0x06, 0x58, 0x10, 0x08, 0x01, 0x01, 0x00,
  0x00, 0x07, 0xc8, 0x07, 0x8c, 0x06, 0x10, 0x00,
  0x00, 0x20, 0x4f, 0x80, 0x00, 0x7f, 0x00, 0x00,
  0x03, 0x07, 0x01, 0x07, 0x01, 0x0c, 0x07, 0x03,
  0x2c, 0x08, 0xfc, 0x80, 0x09, 0x5a, 0x80, 0x0a,
  0xfc, 0x08, 0xfb, 0x80, 0x0b, 0x5a, 0x09, 0x5b,
  0x80, 0x0a, 0xfb, 0x08, 0xfa, 0x80, 0x0b, 0x5b,
  0x09, 0x5c, 0x80, 0x0a, 0xfa, 0x08, 0xf9, 0x80,
  0x0b, 0x5c, 0x09, 0x5d, 0x80, 0x0a, 0xf9, 0x08,
  0xf8, 0x80, 0x0b, 0x5d, 0x09, 0x5e, 0x80, 0x0a,
  0xf8, 0x08, 0xf7, 0x80, 0x0b, 0x5e, 0x09, 0x5f,
  0x80, 0x0a, 0xf7, 0x08, 0xf6, 0x80, 0x0b, 0x5f,
  0x09, 0x60, 0x80, 0x0a, 0xf6, 0x08, 0xf5, 0x80,
  0x0b, 0x60, 0x09, 0x61, 0x80, 0x0a, 0xf5, 0x08,
  0xf4, 0x80, 0x0b, 0x61, 0x09, 0x62, 0x80, 0x0a,
  0xf4, 0x08, 0xf3, 0x80, 0x0b, 0x62, 0x09, 0x63,
  0x80, 0x0a, 0xf3, 0x08, 0xf2, 0x80, 0x0b, 0x63,
  0x09, 0x64, 0x80, 0x0a, 0xf2, 0x08, 0xf1, 0x80,
  0x0b, 0x64, 0x09, 0x65, 0x80, 0x0a, 0xf1, 0x08,
  0xf0, 0x80, 0x0b, 0x65, 0x09, 0x66, 0x80, 0x0a,
  0xf0, 0x08, 0xef, 0x80, 0x0b, 0x66, 0x09, 0x67,
  0x80, 0x0a, 0xef, 0x08, 0xee, 0x80, 0x0b, 0x67,
  0x09, 0x68, 0x80, 0x0a, 0xee, 0x08, 0xed, 0x80,
  0x0b, 0x68, 0x09, 0x6c, 0x80, 0x0a, 0xed, 0x08,
  0xec, 0x80, 0x0b, 0x6c, 0x09, 0x6d, 0x80, 0x0a,
  0xec, 0x08, 0xeb, 0x80, 0x0b, 0x6d, 0x09, 0x6e,
  0x80, 0x0a, 0xeb, 0x08, 0xea, 0x80, 0x0b, 0x6e,
  0x09, 0x6f, 0x80, 0x0a, 0xea, 0x08, 0xe9, 0x80,
  0x0b, 0x6f, 0x09, 0x70, 0x80, 0x0a, 0xe9, 0x08,
  0xe8, 0x80, 0x0b, 0x70, 0x09, 0x71, 0x80, 0x0a,
  0xe8, 0x08, 0xe7, 0x80, 0x0b, 0x71, 0x09, 0x72,
  0x80, 0x0a, 0xe7, 0x08, 0xe6, 0x80, 0x0b, 0x72,
  0x09, 0x73, 0x80, 0x0a, 0xe6, 0x08, 0xe5, 0x80,
  0x0b, 0x73, 0x09, 0x74, 0x80, 0x0a, 0xe5, 0x08,
  0xe4, 0x80, 0x0b, 0x74, 0x09, 0x75, 0x80, 0x0a,
  0xe4, 0x08, 0xe3, 0x80, 0x0b, 0x75, 0x09, 0x76,
  0x80, 0x0a, 0xe3, 0x08, 0xe2, 0x80, 0x0b, 0x76,
  0x09, 0x77, 0x80, 0x0a, 0xe2, 0x08, 0xe1, 0x80,
  0x0b, 0x77, 0x09, 0x78, 0x80, 0x0a, 0xe1, 0x08,
  0xe0, 0x80, 0x0b, 0x78, 0x09, 0x79, 0x80, 0x0a,
  0xe0, 0x08, 0xdf, 0x80, 0x0b, 0x79, 0x09, 0x7a,
  0x80, 0x0a, 0xdf, 0x08, 0xde, 0x80, 0x0b, 0x7a,
  0x09, 0x7b, 0x80, 0x0a, 0xde, 0x08, 0xdd, 0x80,
  0x0b, 0x7b, 0x09, 0x7c, 0x80, 0x0a, 0xdd, 0x08,
  0xdc, 0x80, 0x0b, 0x7c, 0x09, 0x7d, 0x80, 0x0a,
  0xdc, 0x08, 0xdb, 0x80, 0x0b, 0x7d, 0x09, 0x7e,
  0x80, 0x0a, 0xdb, 0x08, 0xda, 0x80, 0x0b, 0x7e,
  0x09, 0x7f, 0x80, 0x0a, 0xda, 0x08, 0xd9, 0x80,
  0x0b, 0x7f, 0x09, 0x80, 0x80, 0x0a, 0xd9, 0x08,
  0xd8, 0x80, 0x0b, 0x80, 0x09, 0x81, 0x80, 0x0a,
  0xd8, 0x08, 0xd7, 0x80, 0x0b, 0x81, 0x09, 0x82,
  0x80, 0x0a, 0xd7, 0x08, 0xd6, 0x80, 0x0b, 0x82,
  0x09, 0x83, 0x80, 0x0a, 0xd6, 0x08, 0xd5, 0x80,
  0x0b, 0x83, 0x09, 0x84, 0x80, 0x0a, 0xd5, 0x08,
  0xd4, 0x80, 0x0b, 0x84, 0x09, 0x85, 0x80, 0x0a,
  0xd4, 0x08, 0xd3, 0x80, 0x0b, 0x85, 0x09, 0x86,
  0x80, 0x0a, 0xd3, 0x08, 0xd2, 0x80, 0x0b, 0x86,
  0x09, 0x87, 0x80, 0x0a, 0xd2, 0x08, 0xd1, 0x80,
  0x0b, 0x87, 0x09, 0x88, 0x80, 0x0a, 0xd1, 0x08,
  0xd0, 0x80, 0x0b, 0x88, 0x09, 0x89, 0x80, 0x0a,
  0xd0, 0x08, 0xcf, 0x80, 0x0b, 0x89, 0x09, 0x8a,
  0x80, 0x0a, 0xcf, 0x08, 0xce, 0x80, 0x0b, 0x8a,
  0x09, 0x8b, 0x80, 0x0a, 0xce, 0x08, 0xcd, 0x80,
  0x0b, 0x8b, 0x09, 0x8c, 0x80, 0x0a, 0xcd, 0x08,
  0xcc, 0x80, 0x0b, 0x8c, 0x09, 0x8d, 0x80, 0x0a,
  0xcc, 0x08, 0xcb, 0x80, 0x0b, 0x8d, 0x09, 0x8e,
  0x80, 0x0a, 0xcb, 0x08, 0xca, 0x80, 0x0b, 0x8e,
  0x09, 0x8f, 0x80, 0x0a, 0xca, 0x08, 0xc9, 0x80,
  0x0b, 0x8f, 0x09, 0x90, 0x80, 0x0a, 0xc9, 0x08,
  0xc8, 0x80, 0x0b, 0x90, 0x09, 0x91, 0x80, 0x0a,
  0xc8, 0x08, 0xc7, 0x80, 0x0b, 0x91, 0x09, 0x92,
  0x80, 0x0a, 0xc7, 0x08, 0xc6, 0x80, 0x0b, 0x92,
  0x09, 0x93, 0x80, 0x0a, 0xc6, 0x08, 0xc5, 0x80,
  0x0b, 0x93, 0x09, 0x94, 0x80, 0x0a, 0xc5, 0x08,
  0xc4, 0x80, 0x0b, 0x94, 0x09, 0x95, 0x80, 0x0a,
  0xc4, 0x08, 0xc3, 0x80, 0x0b, 0x95, 0x09, 0x96,
  0x80, 0x0a, 0xc3, 0x08, 0xc2, 0x80, 0x0b, 0x96,
  0x09, 0x97, 0x80, 0x0a, 0xc2, 0x08, 0xc1, 0x80,
  0x0b, 0x97, 0x09, 0x98, 0x80, 0x0a, 0xc1, 0x08,
  0xc0, 0x80, 0x0b, 0x98, 0x09, 0x99, 0x80, 0x0a,
  0xc0, 0x08, 0xbf, 0x80, 0x0b, 0x99, 0x09, 0x9a,
  0x80, 0x0a, 0xbf, 0x08, 0xbe, 0x80, 0x0b, 0x9a,
  0x09, 0x9b, 0x80, 0x0a, 0xbe, 0x08, 0xbd, 0x80,
  0x0b, 0x9b, 0x09, 0x9c, 0x80, 0x0a, 0xbd, 0x08,
  0xbc, 0x80, 0x0b, 0x9c, 0x09, 0x9d, 0x80, 0x0a,
  0xbc, 0x08, 0xbb, 0x80, 0x0b, 0x9d, 0x09, 0x9e,
  0x80, 0x0a, 0xbb, 0x08, 0xba, 0x80, 0x0b, 0x9e,
  0x09, 0x9f, 0x80, 0x0a, 0xba, 0x08, 0xb9, 0x80,
  0x0b, 0x9f, 0x09, 0xa0, 0x80, 0x0a, 0xb9, 0x08,
  0xb8, 0x80, 0x0b, 0xa0, 0x08, 0x01, 0x80, 0x0a,
  0xb8, 0x08, 0xb7, 0x80, 0x0a, 0x01, 0x08, 0x02,
  0x80, 0x0a, 0xb7, 0x08, 0xb6, 0x80, 0x0a, 0x02,
  0x08, 0x03, 0x80, 0x0a, 0xb6, 0x08, 0xb5, 0x80,
  0x0a, 0x03, 0x08, 0x04, 0x80, 0x20, 0x03, 0x07,
  0x04, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x2f, 0x00, 0x04, 0x00, 0x90, 0x00, 0x00,
  0x00, 0x29, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x35, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00,
  0x00, 0x17, 0x00, 0x00, 0x00, 0x26, 0x00, 0x28,
  0x00, 0xfb, 0xb2, 0x0f, 0x00, 0x00, 0x00, 0x0f,
  0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x01, 0x02,
  0x00, 0x40, 0x01, 0x0a, 0x00, 0x01, 0x80, 0x00,
  0x00, 0x0a, 0x02, 0x00, 0x00, 0x0b, 0x19, 0x00,
  0x00, 0x50, 0xc3, 0x60, 0xea, 0x01, 0x09, 0x10,
  0x00, 0x2e, 0x00, 0x1c, 0x00, 0x02, 0x00, 0x18,
  0x00, 0x23, 0x00, 0x00, 0x00, 0x90, 0x00, 0x90,
  0x00, 0x4d, 0x01, 0x00, 0x00, 0x90, 0x01, 0x7c,
  0x01, 0x3c, 0x32, 0x32, 0x32, 0x64, 0x0a, 0x02,
  0x01, 0x30, 0x00, 0xcc, 0x01, 0x03, 0x00, 0x00,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00,
  0x03, 0xff, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00,
  0x03, 0xff, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00,
  0x03, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
  0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e,
  0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
  0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e,
  0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
  0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e,
  0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
  0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e,
  0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56,
  0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e,
  0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
  0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
  0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
  0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e,
  0x7f, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86,
  0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e,
  0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,
  0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e,
  0x9f, 0x14, 0x24, 0x44, 0x36, 0x52, 0x3c, 0x28,
  0x40, 0x2a, 0x42, 0x2e, 0x46, 0x32, 0x48, 0x34,
  0x48, 0x32, 0x4a, 0x34, 0x4c, 0x32, 0x4c, 0x36,
  0x52, 0x38, 0x50, 0x3a, 0x50, 0x3a, 0x4e, 0x38,
  0x50, 0x3a, 0x54, 0x38, 0x52, 0x38, 0x50, 0x3a,
  0x50, 0x38, 0x50, 0x3a, 0x52, 0x3e, 0x28, 0x3c,
  0x28, 0x3e, 0x28, 0x28, 0x28, 0x28, 0x28, 0x3c,
  0x28, 0x28, 0x28, 0x3e, 0x2a, 0x28, 0x28, 0x28,
  0x28, 0x3c, 0x28, 0x3a, 0x48, 0x46, 0x3c, 0x50,
  0x3c, 0x28, 0x38, 0x4e, 0x28, 0x4e, 0x28, 0x28,
  0x3e, 0x28, 0x28, 0x28, 0x3c, 0x4e, 0x3a, 0x28,
  0x3a, 0x50, 0x3c, 0x28, 0x28, 0x50, 0x3a, 0x28,
  0x3e, 0x28, 0x28, 0x2c, 0x28, 0x28, 0x28, 0x28,
  0x3e, 0x28, 0x3e, 0x28, 0x38, 0x28, 0x3e, 0x28,
  0x28, 0x4c, 0x3a, 0x28, 0x3c, 0x28, 0x3a, 0x28,
  0x3a, 0x4c, 0x3a, 0x4a, 0x3c, 0x4c, 0x3a, 0x4c,
  0x3a, 0x4a, 0x38, 0x28, 0x3a, 0x4a, 0x38, 0x38,
  0x3a, 0x38, 0x34, 0x34, 0x34, 0x32, 0x28, 0x1a,
  0x12, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x80,
  0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80,
  0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80,
  0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80,
  0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80,
  0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x81, 0x80, 0x81, 0x80, 0x80,
  0x80, 0x81, 0x80, 0x80, 0x80, 0x81, 0x80, 0x81,
  0x80, 0x80, 0x80, 0x80, 0x7f, 0x7f, 0x80, 0x7f,
  0x80, 0x80, 0x80, 0x7f, 0x81, 0x7f, 0x81, 0x80,
  0x80, 0x80, 0x81, 0x80, 0x80, 0x7f, 0x80, 0x80,
  0x80, 0x7f, 0x80, 0x80, 0x81, 0x7f, 0x80, 0x80,
  0x80, 0x80, 0x81, 0x80, 0x81, 0x80, 0x81, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x81, 0x7f, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f,
  0x80, 0x7f, 0x80, 0x80, 0x80, 0x7f, 0x80, 0x7f,
  0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0x7f,
  0x7f
};

static const VfsDataExchange ACTIVATE_SEQUENCES[] = {
  {
    .msg = ACTIVATE_SEQUENCE_MSG1,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG1),
    .rsp = (unsigned char[]){ 0x00, 0x00 },
    .rsp_length = 2,
  },
  {
    .msg = ACTIVATE_SEQUENCE_MSG2,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG2),
    .rsp = (unsigned char[]){ 0x00, 0x00, 0x02, 0x00, 0x00, 0x00 },
    .rsp_length = 6,
  },
  {
    .weak_match = TRUE,
    .msg = ACTIVATE_SEQUENCE_MSG345,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG345),
    .rsp = ACTIVATE_SEQUENCE_RSP345,
    .rsp_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_RSP345),
  },
  {
    .weak_match = TRUE,
    .msg = ACTIVATE_SEQUENCE_MSG345,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG345),
    .rsp = ACTIVATE_SEQUENCE_RSP345,
    .rsp_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_RSP345),
  },
  {
    .weak_match = TRUE,
    .msg = ACTIVATE_SEQUENCE_MSG345,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG345),
    .rsp = ACTIVATE_SEQUENCE_RSP345,
    .rsp_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_RSP345),
  },
  {
    //.weak_match = TRUE,
    .msg = ACTIVATE_SEQUENCE_MSG67,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG67),
    .rsp = NULL,
    .rsp_length = 108,
  },
  {
    //.weak_match = TRUE, 
    .msg = ACTIVATE_SEQUENCE_MSG67,
    .msg_length = G_N_ELEMENTS (ACTIVATE_SEQUENCE_MSG67),
    .rsp = NULL,
    .rsp_length = 108,
  },
  {
    .msg = SCAN_MATRIX,
    .msg_length = G_N_ELEMENTS (SCAN_MATRIX),
    .rsp = NULL,
    .rsp_length = -1 /* 2366 or 2 */,
  },
};

static const VfsDataExchange MATRIX_ALREADY_ACTIVATED_DEX = {
  .msg = SCAN_MATRIX,
  .msg_length = G_N_ELEMENTS (SCAN_MATRIX),
  .rsp = (unsigned char[]){ 0x50, 0x04 },
  .rsp_length = 2,
};

static const unsigned char DB_DUMP_STGWINDSOR[] = {
  /* Dump DB for StgWindsor user */
  0x4b, 0x00, 0x00, 0x0b, 0x00, 0x53, 0x74, 0x67,
  0x57, 0x69, 0x6e, 0x64, 0x73, 0x6f, 0x72, 0x00
};

static const VfsDataExchange DB_IDENTIFY_SEQUENCES[] = {
  {
    .msg = (unsigned char *) &((VfsDbIdentifyQuery){
      .request_id = 0x5e,
      .unknowns1 = { 0x02, 0xff },
      .storage_id = 0,
      .user_id = 0,
      .unknowns2 = { 1, 0, 0 },
    }),
    .msg_length = sizeof (VfsDbIdentifyQuery),
    .rsp = (unsigned char[]){ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    .rsp_length = 6,
  },
  {
    .msg = (unsigned char[]){ 0x60, 0x00, 0x00, 0x00, 0x00 },
    .msg_length = 5,
    /* The response here contains the details on database matching */
    .rsp_length = -1,
  },
};

static const VfsDataExchange DEACTIVATE_SEQUENCES[] = {
  {
    .msg = (unsigned char[]){ 0x62, 0x00, 0x00, 0x00, 0x00 },
    .msg_length = 5,
    .rsp = (unsigned char[]){ 0x00, 0x00 },
    .rsp_length = 2,
  },
};


static unsigned char LED_OFF[] = {
  0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char LED_GREEN_ON[] = {
  0x39, 0x20, 0xbf, 0x02, 0x00, 0xff, 0xff, 0x00,
  0x00, 0x01, 0x99, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
  0x00, 0x00, 0x99, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char LED_RED_BLINK[] = {
  0x39, 0xee, 0x02, 0x00, 0x00, 0x4b, 0x00, 0x00,
  0x00, 0x01, 0xff, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
  0x00, 0x4b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x4b, 0x00, 0x00,
  0x00, 0x01, 0xff, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x4b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned char LED_GREEN_BLINK[] = {
  0x39, 0xf4, 0x01, 0x00, 0x00, 0xf4, 0x01, 0x00,
  0x00, 0x01, 0xff, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x01, 0x00,
  0x00, 0x00, 0xff, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};
