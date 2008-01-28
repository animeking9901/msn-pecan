/*
 * Copyright (C) 2008 Felipe Contreras.
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MSN_CMD_CONN_PRIVATe_H
#define MSN_CMD_CONN_PRIVATe_H

#include <glib-object.h>

typedef struct PecanCmdServerClass PecanCmdServerClass;

#include "pecan_node_priv.h"
#include "pecan_cmd_server.h"

struct MsnCmdProc;

struct PecanCmdServer
{
    PecanNode parent;
    gboolean dispose_has_run;

    gsize payload_len;
    gchar *rx_buf;
    gsize rx_len;

    struct MsnCmdProc *cmdproc;
};

struct PecanCmdServerClass
{
    PecanNodeClass parent_class;
};

GType pecan_cmd_server_get_type (void);

#endif /* MSN_CMD_CONN_PRIVATe_H */
