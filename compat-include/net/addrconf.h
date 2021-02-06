/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 *
 * This file contains macros for maintaining compatibility with older versions
 * of the Linux kernel.
 */

#ifndef _NET_BATMAN_ADV_COMPAT_NET_ADDRCONF_H_
#define _NET_BATMAN_ADV_COMPAT_NET_ADDRCONF_H_

#include <linux/version.h>
#include_next <net/addrconf.h>

#if LINUX_VERSION_IS_LESS(5, 1, 0)

static inline int batadv_ipv6_mc_check_mld(struct sk_buff *skb)
{
	return ipv6_mc_check_mld(skb, NULL);
}

#define ipv6_mc_check_mld(skb) \
	batadv_ipv6_mc_check_mld(skb)

#endif /* LINUX_VERSION_IS_LESS(5, 1, 0) */

#endif	/* _NET_BATMAN_ADV_COMPAT_NET_ADDRCONF_H_ */
