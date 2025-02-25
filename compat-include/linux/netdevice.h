/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 *
 * This file contains macros for maintaining compatibility with older versions
 * of the Linux kernel.
 */

#ifndef _NET_BATMAN_ADV_COMPAT_LINUX_NETDEVICE_H_
#define _NET_BATMAN_ADV_COMPAT_LINUX_NETDEVICE_H_

#include <linux/version.h>
#include_next <linux/netdevice.h>

#if LINUX_VERSION_IS_LESS(4, 15, 0)

#define netdev_master_upper_dev_link(dev, upper_dev, upper_priv, upper_info, extack) \
	netdev_master_upper_dev_link(dev, upper_dev, upper_priv, upper_info)

#endif /* LINUX_VERSION_IS_LESS(4, 15, 0) */

#if LINUX_VERSION_IS_LESS(4, 11, 9)

/* work around missing attribute needs_free_netdev and priv_destructor in
 * net_device
 */
#define ether_setup(dev) \
	void batadv_softif_free2(struct net_device *dev) \
	{ \
		batadv_softif_free(dev); \
		free_netdev(dev); \
	} \
	void (*t1)(struct net_device *dev) __attribute__((unused)); \
	bool t2 __attribute__((unused)); \
	ether_setup(dev)
#define needs_free_netdev destructor = batadv_softif_free2; t2
#define priv_destructor destructor = batadv_softif_free2; t1

#endif /* LINUX_VERSION_IS_LESS(4, 11, 9) */


#if LINUX_VERSION_IS_LESS(5, 15, 0)

static inline void batadv_dev_put(struct net_device *dev)
{
	if (!dev)
		return;

	dev_put(dev);
}
#define dev_put batadv_dev_put

static inline void batadv_dev_hold(struct net_device *dev)
{
	if (!dev)
		return;

	dev_hold(dev);
}
#define dev_hold batadv_dev_hold

#endif /* LINUX_VERSION_IS_LESS(5, 15, 0) */

#if LINUX_VERSION_IS_LESS(5, 18, 0)

static inline int batadv_netif_rx(struct sk_buff *skb)
{
	if (in_interrupt())
		return netif_rx(skb);
	else
		return netif_rx_ni(skb);
}
#define netif_rx batadv_netif_rx

#endif /* LINUX_VERSION_IS_LESS(5, 18, 0) */

#endif	/* _NET_BATMAN_ADV_COMPAT_LINUX_NETDEVICE_H_ */
