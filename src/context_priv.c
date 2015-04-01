/*
 *  Off-the-Record Messaging library
 *  Copyright (C) 2004-2012  Ian Goldberg, Chris Alexander, Willy Lew,
 *			     Nikita Borisov
 *                           <otr@cypherpunks.ca>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of version 2.1 of the GNU Lesser General
 *  Public License as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* system headers */
#include <stdlib.h>

/* libgcrypt headers */
#include <gcrypt.h>

/* libotr headers */
#include "context_priv.h"

/* Create a new private connection context */
ConnContextPriv *otrl_context_priv_new()
{
	return calloc(1, sizeof(ConnContextPriv));
}

/* Resets the appropriate variables when a context
 * is being force finished
 */
void otrl_context_priv_force_finished(ConnContextPriv *context_priv)
{
	free(context_priv->fragment);
	free(context_priv->saved_mac_keys);
	gcry_free(context_priv->lastmessage);
	gcry_mpi_release(context_priv->their_y);
	gcry_mpi_release(context_priv->their_old_y);
	otrl_dh_keypair_free(&(context_priv->our_dh_key));
	otrl_dh_keypair_free(&(context_priv->our_old_dh_key));
	otrl_dh_session_free(&(context_priv->sesskeys[0][0]));
	otrl_dh_session_free(&(context_priv->sesskeys[0][1]));
	otrl_dh_session_free(&(context_priv->sesskeys[1][0]));
	otrl_dh_session_free(&(context_priv->sesskeys[1][1]));

	memset(context_priv, 0, sizeof(ConnContextPriv));
}
