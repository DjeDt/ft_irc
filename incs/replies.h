/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:17:33 by ddinaut           #+#    #+#             */
/*   Updated: 2019/09/03 17:04:47 by ddinaut          ###   ########.fr       */
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

/*
** Error replies string following rfc 1459
*/
# define ERR_NOSUCHNICK			"401 <nickname> :No such nick/channel"
# define ERR_NOSUCHSERVER		"402 <server name> :No such server"
# define ERR_NOSUCHCHANNEL		"403 <channel name> :No such channel"
# define ERR_CANNOTSENDTOCHAN	"404 <channel name> :Cannot send to channel"
# define ERR_TOOMANYCHANNELS	"405 <channel name> :You have joined too many channels"
# define ERR_NORECIPIENT		"411 :No recipient given (<command>)"
# define ERR_NOTEXTTOSEND		"412 :No text to send"
# define ERR_UNKNOWNCOMMAND		"421 <%s> :Unknown command"

# define ERR_NONICKNAMEGIVEN	"431 :No nickname given"
# define ERR_ERRONEUSNICKNAME	"432 <nick> :Erroneus nickname"
# define ERR_NICKNAMEINUSE		"433 <nick> :Nickname is already in use"
# define ERR_NICKCOLLISION		"436 <nick> :Nickname collision KILL"

# define ERR_USERNOTINCHANNEL	"441 <nick> <channel> :They aren' on that channel"
# define ERR_NOTONCHANNEL		"442 <channel> :You're not on that channel"
# define ERR_NOLOGIN			"444 <user> :User not logged in"
# define ERR_NEEDMOREPARAMS		"461 <command> :Not enough parameters"
# define ERR_CANTKILLSERVER		"483 :You cant kill a server"

/*
** Normal replies
*/

# define RPL_LISTSTART_ID			321
# define RPL_LIST_ID				322
# define RPL_LISTEND_ID				323

# define RPL_LISTSTART			"321 Channel :Users  Name"
# define RPL_LIST				"322 <channel> <user visible>"
# define RPL_LISTEND			"323 End of /LIST"

#endif
