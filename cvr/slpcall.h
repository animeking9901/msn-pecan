/**
 * Copyright (C) 2008-2009 Felipe Contreras
 * Copyright (C) 1998-2006 Pidgin (see pidgin-copyright)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef MSN_SLPCALL_H
#define MSN_SLPCALL_H

typedef struct MsnSlpCall MsnSlpCall;

struct MsnSession;
struct PnPeerLink;

#include <glib.h>

typedef enum {
    MSN_SLPCALL_ANY,
    MSN_SLPCALL_DC,
} MsnSlpCallType;

struct MsnSlpCall
{
    MsnSlpCallType type;

    char *id;
    char *branch;

    long session_id;
    long app_id;

    gboolean pending; /**< A flag that states if we should wait for this
                        slpcall to start and do not time out. */
    gboolean progress; /**< A flag that states if there has been progress since
                         the last time out. */
    gboolean wasted; /**< A flag that states if this slpcall is going to be
                       destroyed. */
    gboolean started; /**< A flag that states if this slpcall's session has
                        been initiated. */

    void (*progress_cb)(MsnSlpCall *slpcall,
                        gsize total_length, gsize len, gsize offset);
    void (*init_cb)(MsnSlpCall *slpcall);

    /* Can be checksum, or smile */
    char *data_info;

    void *xfer;

    void (*cb)(MsnSlpCall *slpcall, const guchar *data, gsize size);
    void (*end_cb)(MsnSlpCall *slpcall, struct MsnSession *session);

    int timer;

    struct PnPeerLink *link;
};

MsnSlpCall *msn_slp_call_new(struct PnPeerLink *link);
void msn_slp_call_init(MsnSlpCall *slpcall,
                       MsnSlpCallType type);
void msn_slp_call_session_init(MsnSlpCall *slpcall);
void msn_slp_call_destroy(MsnSlpCall *slpcall);
void msn_slp_call_invite(MsnSlpCall *slpcall,
                         const char *euf_guid,
                         int app_id,
                         const char *context);
void msn_slp_call_close(MsnSlpCall *slpcall);
gboolean msn_slp_call_timeout(gpointer data);

#endif /* MSN_SLPCALL_H */
