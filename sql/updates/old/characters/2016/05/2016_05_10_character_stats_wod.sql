DROP TABLE IF EXISTS `character_stats_wod`;

CREATE TABLE `character_stats_wod` (
  `guid` INT(11) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier, Low part',
  `strength` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `agility` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `stamina` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `intellect` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `critPct` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `haste` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `mastery` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `spirit` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `armorBonus` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `multistrike` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `leech` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `versatility` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `avoidance` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `attackDamage` VARCHAR(255) NOT NULL,
  `attackPower` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `attackSpeed` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `spellPower` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `manaRegen` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `armor` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  `dodgePct` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `parryPct` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `blockPct` FLOAT UNSIGNED NOT NULL DEFAULT '0',
  `ilvl` INT(10) UNSIGNED NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=INNODB DEFAULT CHARSET=utf8;