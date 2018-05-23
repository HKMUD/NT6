/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50146
Source Host           : localhost:3306
Source Database       : nitan

Target Server Type    : MYSQL
Target Server Version : 50146
File Encoding         : 65001

Date: 2014-11-10 20:40:56
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `cards`
-- ----------------------------
DROP TABLE IF EXISTS `cards`;
CREATE TABLE `cards` (
  `card` varchar(20) NOT NULL DEFAULT '',
  `password` varchar(20) NOT NULL DEFAULT '',
  `money` int(11) DEFAULT '0',
  `maketime` int(11) DEFAULT '0',
  `makeid` varchar(10) NOT NULL DEFAULT '',
  `sale` int(2) DEFAULT '0',
  `paytime` int(11) DEFAULT '0',
  `payid` varchar(10) NOT NULL DEFAULT '',
  PRIMARY KEY (`card`),
  KEY `password` (`password`),
  KEY `money` (`money`),
  KEY `sale` (`sale`),
  KEY `payid` (`payid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of cards
-- ----------------------------

-- ----------------------------
-- Table structure for `ip`
-- ----------------------------
DROP TABLE IF EXISTS `ip`;
CREATE TABLE `ip` (
  `ipstart` varchar(12) NOT NULL DEFAULT '',
  `ipend` varchar(12) NOT NULL DEFAULT '',
  `place` varchar(50) NOT NULL DEFAULT '',
  `address` varchar(100) NOT NULL DEFAULT ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of ip
-- ----------------------------

-- ----------------------------
-- Table structure for `items`
-- ----------------------------
DROP TABLE IF EXISTS `items`;
CREATE TABLE `items` (
  `id` varchar(100) NOT NULL DEFAULT '',
  `dbase` mediumtext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of items
-- ----------------------------

-- ----------------------------
-- Table structure for `members`
-- ----------------------------
DROP TABLE IF EXISTS `members`;
CREATE TABLE `members` (
  `id` varchar(10) NOT NULL DEFAULT '',
  `uid` varchar(10) NOT NULL DEFAULT '',
  `money` int(11) DEFAULT '0',
  `vip` int(2) DEFAULT '0',
  `jointime` int(11) DEFAULT '0',
  `endtime` int(11) DEFAULT '0',
  `paytimes` int(7) DEFAULT '0',
  `payvalue` int(7) DEFAULT '0',
  `buytimes` int(7) DEFAULT '0',
  `buyvalue` int(7) DEFAULT '0',
  `transfertimes` int(7) DEFAULT '0',
  `transfervalue` int(7) DEFAULT '0',
  `last_paytime` int(11) DEFAULT '0',
  `last_buytime` int(11) DEFAULT '0',
  `last_payvalue` int(7) DEFAULT '0',
  `last_buyvalue` int(7) DEFAULT '0',
  `last_buyob` varchar(40) NOT NULL DEFAULT '',
  `payinfo` text NOT NULL,
  `buyinfo` mediumtext NOT NULL,
  `transferinfo` mediumtext NOT NULL,
  PRIMARY KEY (`id`),
  KEY `money` (`money`),
  KEY `vip` (`vip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of members
-- ----------------------------

-- ----------------------------
-- Table structure for `mudlist`
-- ----------------------------
DROP TABLE IF EXISTS `mudlist`;
CREATE TABLE `mudlist` (
  `chinese` varchar(20) NOT NULL DEFAULT '',
  `english` varchar(20) NOT NULL DEFAULT '',
  `ip` varchar(20) NOT NULL DEFAULT '',
  `port` int(6) DEFAULT '0',
  `status` int(2) DEFAULT '0',
  `players` int(11) DEFAULT '0',
  `lasttime` varchar(20) NOT NULL DEFAULT '',
  PRIMARY KEY (`ip`),
  UNIQUE KEY `ip` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of mudlist
-- ----------------------------

-- ----------------------------
-- Table structure for `news`
-- ----------------------------
DROP TABLE IF EXISTS `news`;
CREATE TABLE `news` (
  `title` varchar(100) NOT NULL DEFAULT '',
  `time` int(30) unsigned NOT NULL DEFAULT '0',
  `author` varchar(50) NOT NULL DEFAULT '',
  `msg` text NOT NULL,
  `view` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`time`),
  KEY `title` (`title`,`time`,`author`),
  KEY `view` (`view`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of news
-- ----------------------------

-- ----------------------------
-- Table structure for `register`
-- ----------------------------
DROP TABLE IF EXISTS `register`;
CREATE TABLE `register` (
  `id` varchar(10) NOT NULL DEFAULT '',
  `add_hours` int(11) DEFAULT '0',
  `new_fee_time` int(11) DEFAULT '0',
  `time` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of register
-- ----------------------------

-- ----------------------------
-- Table structure for `updated`
-- ----------------------------
DROP TABLE IF EXISTS `updated`;
CREATE TABLE `updated` (
  `table` varchar(20) NOT NULL DEFAULT '',
  `time` datetime DEFAULT NULL,
  PRIMARY KEY (`table`),
  UNIQUE KEY `table` (`table`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of updated
-- ----------------------------

-- ----------------------------
-- Table structure for `users`
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` varchar(10) NOT NULL DEFAULT '',
  `name` varchar(10) NOT NULL DEFAULT '',
  `surname` varchar(6) NOT NULL DEFAULT '',
  `purename` varchar(6) NOT NULL DEFAULT '',
  `password` varchar(50) NOT NULL DEFAULT '',
  `ad_password` varchar(50) NOT NULL DEFAULT '',
  `birthday` datetime DEFAULT NULL,
  `online` int(2) DEFAULT NULL,
  `on_time` int(11) DEFAULT '0',
  `fee_time` int(11) DEFAULT '30',
  `save_time` datetime DEFAULT NULL,
  `last_from` varchar(15) DEFAULT NULL,
  `last_on` datetime DEFAULT NULL,
  `last_off` datetime DEFAULT NULL,
  `last_station` varchar(15) NOT NULL DEFAULT '',
  `endrgt` date DEFAULT NULL,
  `login_dbase` text,
  `char_idname` text,
  `f_autoload` mediumtext,
  `f_dbase` mediumtext,
  `f_damage` text,
  `f_condition` text,
  `f_attack` text,
  `f_skill` text,
  `f_alias` text,
  `f_user` text,
  `f_business` text,
  `f_mail` mediumtext,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of users
-- ----------------------------
