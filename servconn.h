/**
 * Copyright (C) 2007-2008 Felipe Contreras
 *
 * Purple is the legal property of its developers, whose names are too numerous
 * to list here.  Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */
#ifndef _MSN_SERVCONN_H_
#define _MSN_SERVCONN_H_

typedef struct _MsnServConn MsnServConn;

#include "session.h"
#include "cmdproc.h"

#include "proxy.h"
#include "httpconn.h"

/**
 * Connection error types.
 */
typedef enum
{
    MSN_SERVCONN_ERROR_NONE,
    MSN_SERVCONN_ERROR_CONNECT,
    MSN_SERVCONN_ERROR_WRITE,
    MSN_SERVCONN_ERROR_READ,

} MsnServConnError;

/**
 * Connection types.
 */
typedef enum
{
    MSN_SERVCONN_NS,
    MSN_SERVCONN_SB

} MsnServConnType;

/**
 * A Connection.
 */
struct _MsnServConn
{
    MsnServConnType type; /**< The type of this connection. */
    MsnSession *session;  /**< The MSN session of this connection. */
    MsnCmdProc *cmdproc;  /**< The command processor of this connection. */

    ConnEndObject *conn_end;

    GError *error; /**< The current IO error .*/
    guint read_watch; /** < The source id of the read watch. */

    PurpleProxyConnectData *connect_data;

    gboolean connected;   /**< A flag that states if it's connected. */
    gboolean processing;  /**< A flag that states if something is working
                            with this connection. */
    gboolean wasted;      /**< A flag that states if it should be destroyed. */

#if 0
    char *host; /**< The host this connection is connected or should be
                  connected to. */
    int num; /**< A number id of this connection. */

    MsnHttpConn *httpconn; /**< The HTTP connection this connection should use. */

    char *rx_buf; /**< The receive buffer. */
    gsize rx_len; /**< The receive buffer lenght. */

    gsize payload_len; /**< The length of the payload.
                         It's only set when we've received a command that
                         has a payload. */

    PurpleCircBuffer *tx_buf;
    guint tx_handler;
#endif

    void (*destroy_cb)(MsnServConn *); /**< The callback to call when destroying. */
};

/**
 * Creates a new connection object.
 *
 * @param session The session.
 * @param type The type of the connection.
 */
MsnServConn *msn_servconn_new(MsnSession *session, MsnServConnType type);

/**
 * Destroys a connection object.
 *
 * @param servconn The connection.
 */
void msn_servconn_destroy(MsnServConn *servconn);

/**
 * Disconnects.
 *
 * @param servconn The connection.
 */
void msn_servconn_disconnect(MsnServConn *servconn);

/**
 * Sets the destroy callback.
 *
 * @param servconn The servconn that's being destroyed.
 * @param destroy_cb The destroy callback.
 */
void msn_servconn_set_destroy_cb(MsnServConn *servconn,
                                 void (*destroy_cb)(MsnServConn *));

#endif /* _MSN_SERVCONN_H_ */
