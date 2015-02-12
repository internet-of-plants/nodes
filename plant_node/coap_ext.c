/*
 * Copyright (C) 2015 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief       extensions to stock microcoap (might become PRs)
 *
 * @author      Lotte Steenbrink <lotte.steenbrink@haw-hamburg.de>
 *
 * @}
 */

#include "coap_ext.h"

int coap_ext_build_PUT(uint8_t* buf, size_t buflen, char* payload, coap_endpoint_path_t* path)
{
    /* 
     * Note: the resource URI is coded as an option! -> COAP_OPTION_URI_PATH
     */

    return 0;
}

// lucas: PUT /nodes mit payload kann ich ohne probleme annehmen

/* organic, local, gluten-free */
int make_homemade_request(uint8_t* snd_buf)
{
    printf("creating example GET request...\n");
    static char* msg= "hello";
    size_t req_pkt_sz;
    int errcode;

    // cobble together CoAP packet
    coap_header_t req_hdr = {
        .ver = 1,
        .t = COAP_TYPE_NONCON,
        .tkl = 0,                  /* microcoap can't generate tokens anyway */
        .code = MAKE_RSPCODE(0, COAP_METHOD_GET),  /* class 0, detail 1 */
        .id = {22,22}              /*let's see if this works :D */
    };

    coap_buffer_t payload = {
        .p = (const uint8_t *) msg,
        .len = strlen(msg)
    };

    coap_packet_t req_pkt = {
        .hdr = req_hdr,
        .tok = (coap_buffer_t) {}, /* No token */
        .numopts = 0,
        .opts = {},
        .payload = payload
    };

    req_pkt_sz = sizeof(req_pkt);

#ifdef DEBUG
    printf("[main-posix] content:\n");
    coap_dumpPacket(&req_pkt);
#endif

    // try to  write packet to send buffer
    if (0 != (errcode = coap_build(snd_buf, &req_pkt_sz, &req_pkt))) {
        printf("Error building packet! Error code: %i\nAborting. \n", errcode);
        return 1;
    }
    return 0;
}
