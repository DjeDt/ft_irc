/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:17:33 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/10 20:10:45 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_H
# define REPLIES_H

/*
** Error replies id following rfc 1459 used by our error manager
*/

# define ERR_NOSUCHNICK_ID			401
# define ERR_NOSUCHSERVER_ID		402
# define ERR_NOSUCHCHANNEL_ID		403
# define ERR_CANNOTSENDTOCHAN_ID	404
# define ERR_TOOMANYCHANNELS_ID		405
# define ERR_NORECIPIENT_ID			411
# define ERR_NOTEXTTOSEND_ID		412
# define ERR_UNKNOWNCOMMAND_ID		421

# define ERR_NONICKNAMEGIVEN_ID		431
# define ERR_ERRONEUSNICKNAME_ID	432
# define ERR_NICKNAMEINUSE_ID		433
# define ERR_NICKCOLLISION_ID		436

# define ERR_USERNOTINCHANNEL_ID	441
# define ERR_NOTONCHANNEL_ID		442
# define ERR_NOLOGIN_ID				444
# define ERR_NEEDMOREPARAMS_ID		461
# define ERR_CANTKILLSERVER_ID		483

# define ERR_TOPICTOOLONG_ID		499
# define ERR_ERRONEUSCHANNAME_ID	500

/*
** Error replies string following rfc 1459
*/
# define ERR_NOSUCHNICK			"[server] <%s> :No such nick/channel."	// nickname
# define ERR_NOSUCHSERVER		"[server] <%s> :No such server."			// server name
# define ERR_NOSUCHCHANNEL		"[server] <%s> :No such channel." // channel name
# define ERR_CANNOTSENDTOCHAN	"[server] <%s> :Cannot send to channel." // channel name
# define ERR_TOOMANYCHANNELS	"[server] <%s> :You have joined too many channels." // channel name
# define ERR_NORECIPIENT		"[server] :No recipient given (<%s>)." // command
# define ERR_NOTEXTTOSEND		"[server] :No text to send."
# define ERR_UNKNOWNCOMMAND		"[server] <%s> :Unknown command." // command

# define ERR_NONICKNAMEGIVEN	"[server] :No nickname given."
# define ERR_ERRONEUSNICKNAME	"[server] <%s> :Erroneus nickname." // nickname
# define ERR_ERRONEUSCHANNAME	"[server] <%s> :Erroneus chan name." // channel
# define ERR_NICKNAMEINUSE		"[server] <%s> :Nickname is already in use." // nickname
# define ERR_NICKCOLLISION		"[server] <%s> :Nickname collision KILL." // nickname

# define ERR_USERNOTINCHANNEL	"[server] <%s> <%s> :They aren' on that channel." // nick / channel
# define ERR_NOTONCHANNEL		"[server] <%s> :You're not on that channel." // channel
# define ERR_NOLOGIN			"[server] <%s> :User not logged in." // user
# define ERR_NEEDMOREPARAMS		"[server] <%s> :Not enough parameters." // command
# define ERR_CANTKILLSERVER		"[server] :You cant kill a server."

/*
** Normal replies
*/
# define RPL_LISTSTART_ID			321
# define RPL_LIST_ID				322
# define RPL_LISTEND_ID				323

# define RPL_LISTSTART			"[server] Channel :Users  Name"
# define RPL_LIST				"[server] <%s> <%d>"
# define RPL_ENDOFLIST			"[server] End of /list."

# define RPL_TOPIC				"[server] <%s> :<%s>." // canal / subject
# define RPL_NOTOPIC			"[server] <%s> :No topic is set." // channel

# define RPL_NAMREPLY			"[server] <%s> :<%s>." // channel / nickname
# define RPL_ENDOFNAMES			"[server] <%s> :End of /NAMES list." // channel

# define RPL_WHOREPLY			"[server] <%s> :<%s>." // channel / nickname
# define RPL_ENDOFWHO			"[server] <%s> :End of /NAMES list." // channel

#endif
