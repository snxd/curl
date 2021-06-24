#ifndef HEADER_CURL_MD4_H
#define HEADER_CURL_MD4_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2020, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include "curl_setup.h"

#if !defined(CURL_DISABLE_CRYPTO_AUTH)
#include "curl_hmac.h"

#define MD4_DIGEST_LENGTH 16

typedef CURLcode (* Curl_MD4_init_func)(void *context);
typedef void (* Curl_MD4_update_func)(void *context,
                                      const unsigned char *data,
                                      unsigned int len);
typedef void (* Curl_MD4_final_func)(unsigned char *result, void *context);

struct MD4_params {
  Curl_MD4_init_func     md4_init_func;   /* Initialize context procedure */
  Curl_MD4_update_func   md4_update_func; /* Update context with data */
  Curl_MD4_final_func    md4_final_func;  /* Get final result procedure */
  unsigned int           md4_ctxtsize;  /* Context structure size */
  unsigned int           md4_resultlen; /* Result length (bytes) */
};

struct MD4_context {
  const struct MD4_params *md4_hash;    /* Hash function definition */
  void                  *md4_hashctx;   /* Hash function context */
};

extern const struct MD4_params Curl_DIGEST_MD4[1];
extern const struct HMAC_params Curl_HMAC_MD4[1];

void Curl_md4it(unsigned char *output, const unsigned char *input,
                const size_t len);

struct MD4_context *Curl_MD4_init(const struct MD4_params *md4params);
CURLcode Curl_MD4_update(struct MD4_context *context,
                         const unsigned char *data,
                         unsigned int len);
CURLcode Curl_MD4_final(struct MD4_context *context, unsigned char *result);

#endif /* !defined(CURL_DISABLE_CRYPTO_AUTH) */

#endif /* HEADER_CURL_MD4_H */
