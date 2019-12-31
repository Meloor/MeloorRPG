//
//  GameCfg.h
//  OzgGameRPG
//
//  Created by ozg on 14-3-18.
//
//

#ifndef __GameGlobalConfig_H__
#define __GameGlobalConfig_H__

#define GAME_SYS_DB "db.sys" //ϵͳ���ݿ�
#define GAME_SCENE 0.5 //�����л���ʱ��

#define GAME_TMX_ROLE_WIDTH 32.0
#define GAME_TMX_ROLE_HEIGHT 32.0
#define GAME_PLAYER_MOVESPEED 0.25

#define GAME_MAP_ENCOUNTER 0.025 //������

#define GAME_INIT_SQL "insert into save_data (map_id, player_to_x, player_to_y, player_direction, gold, window_style) values(1, 14.5, 9.5, 'down', 200, 'style2');"

#define GAME_BATTLE_SELECTED_ID "GAME_BATTLE_SELECTED_ID" //ս������ѡ����һ�����ܻ���ߺ���ʱ����ļ���id�����id
#define GAME_BATTLE_FIELD "GAME_BATTLE_FIELD" //ս�������ִ����ϼ��ܻ���߶�����Ӱ�����ĸ��ֶ�

#define GAME_STYLE "GAME_STYLE" //��ǰʹ�õ���ʽ

#define MAX_GOLD 999999 //��Ǯ���ֵ
#define MAX_STATUS1 9999 //HP���ֵ
#define MAX_STATUS2 999 //MP�������������������ٶȡ����ܹ��������ܷ��������ֵ
#define MAX_ITEMS_TOTAL 99 //�����Ʒ��

#define GAME_BG_AUDIO_VOLUME "GAME_BG_AUDIO_VOLUME" //�������ִ�С
#define GAME_EFFECT_AUDIO_VOLUME "GAME_EFFECT_AUDIO_VOLUME" //Ч������С

#define GAME_MAPSHOP_NPC_ID 7 //�̵�NPC��id
#define GAME_MAPINN_NPC_ID 8 //�ù�NPC��id
#define GAME_INN 100 //ס��һ�λ��Ѷ���Ǯ

#endif/*#define __GameGlobalConfig_H__*/
