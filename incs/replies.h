/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:17:33 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/13 17:18:52 by ddinaut          ###   ########.fr       */
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
# define ERR_NOSUCHNICK			"[server] <%s> :No such nick/channel.\r\n"
# define ERR_NOSUCHSERVER		"[server] <%s> :No such server.\r\n"
# define ERR_NOSUCHCHANNEL		"[server] <%s> :No such channel.\r\n"
# define ERR_CANNOTSENDTOCHAN	"[server] <%s> :Cannot send to channel.\r\n"
# define ERR_TOOMANYCHANNELS	"[server] <%s> :You joined too many chan.\r\n"

# define ERR_NORECIPIENT		"[server] :No recipient given (<%s>).\r\n"
# define ERR_NOTEXTTOSEND		"[server] :No text to send.\r\n"
# define ERR_UNKNOWNCOMMAND		"[server] <%s> :Unknown command.\r\n"

# define ERR_NONICKNAMEGIVEN	"[server] :No nickname given.\r\n"
# define ERR_ERRONEUSNICKNAME	"[server] <%s> :Erroneus nickname.\r\n"
# define ERR_ERRONEUSCHANNAME	"[server] <%s> :Erroneus chan name.\r\n"
# define ERR_NICKNAMEINUSE		"[server] <%s> :Nickname is already in use.\r\n"
# define ERR_NICKCOLLISION		"[server] <%s> :Nickname collision KILL.\r\n"

# define ERR_USERNOTINCHANNEL	"[server] <%s> <%s> :not on that channel.\r\n"
# define ERR_NOTONCHANNEL		"[server] <%s> :You're not on that channel.\r\n"
# define ERR_NOLOGIN			"[server] <%s> :User not logged in.\r\n"
# define ERR_NEEDMOREPARAMS		"[server] <%s> :Not enough parameters.\r\n"
# define ERR_CANTKILLSERVER		"[server] :You cant kill a server.\r\n"

/*
** Normal replies
*/
# define RPL_LISTSTART_ID		321
# define RPL_LIST_ID			322
# define RPL_LISTEND_ID			323

# define RPL_LISTSTART			"[server] Channel :Users  Name\r\n"
# define RPL_LIST				"[server] <%s> <%d>\r\n"
# define RPL_ENDOFLIST			"[server] End of /list.\r\n"

# define RPL_TOPIC				"[server] <%s> :<%s>.\r\n"
# define RPL_NOTOPIC			"[server] <%s> :No topic is set.\r\n"

# define RPL_NAMREPLY			"[server] <%s> :<%s>.\r\n"
# define RPL_ENDOFNAMES			"[server] <%s> :End of /NAMES list.\r\n"

# define RPL_WHOREPLY			"[server] <%s> :<%s>.\r\n"
# define RPL_ENDOFWHO			"[server] <%s> :End of /NAMES list.\r\n"

/*
** Custom replies
*/
# define ERR_ERRONEUSCHAR		"[server] :Input contain forbidden character.\r\n"
# define JOIN_NOTIF				"[server] :'%s' has joined %s.\r\n"
# define LEAVE_NOTIF			"[server] :'%s' leaved channel.\r\n"
# define LEAVE_CHAN				"[server] :Disconnected from '%s'.\r\n"
# define MESSAGE_STR			"[msg] [%s] :%s\r\n"
# define NICK_RESP				"[server] :You are now known as '%s'.\r\n"
# define NICK_NOTIF				"[server] :'%s' is now known as '%s'.\r\n"
# define QUIT_NOTIF				"[server] :'%s' quit: %s\r\n"
# define TOPIC_TOO_LONG			"[server] :<%s> :Topic too long.\r\n"

#endif
