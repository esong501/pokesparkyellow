.equ LOCALID_ROCKET, 1

Route24_MapScripts::
	.byte 0

Route24_EventScript_Rocket::
	lock
	faceplayer
	compare VAR_MAP_SCENE_ROUTE24, 1
	goto_if_eq Route24_EventScript_RocketPostBattle
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Route24_EventScript_NoRoomForNugget
	call Route24_EventScript_BattleRocket
	release
	end

Route24_EventScript_NoRoomForNugget::
	msgbox Route24_Text_YouDontHaveAnyRoom
	release
	end

Route24_EventScript_RocketPostBattle::
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	release
	end

Route24_EventScript_RocketTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto Route24_EventScript_RocketTrigger
	end

Route24_EventScript_RocketTrigger::
	textcolor 0
	compare VAR_TEMP_1, 0
	call_if_eq Route24_EventScript_RocketApproachPlayer
	compare VAR_TEMP_1, 1
	call_if_eq Route24_EventScript_RocketMotionToPlayer
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox Route24_Text_JustEarnedFabulousPrize
	checkitemspace ITEM_NUGGET, 1
	compare VAR_RESULT, FALSE
	goto_if_eq Route24_EventScript_NoRoomForNuggetTrigger
	call Route24_EventScript_BattleRocket
	releaseall
	end

Route24_EventScript_BattleRocket::
	giveitem_msg Route24_Text_ReceivedNuggetFromMysteryTrainer, ITEM_NUGGET
	message Route24_Text_JoinTeamRocket
	waitmessage
	playbgm MUS_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	setvar VAR_LAST_TALKED, LOCALID_ROCKET
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_6, Route24_Text_RocketDefeat
	msgbox Route24_Text_YoudBecomeTopRocketLeader
	setvar VAR_MAP_SCENE_ROUTE24, 1
	return

Route24_EventScript_RocketApproachPlayer::
	applymovement LOCALID_ROCKET, Route24_Movement_RocketApproachPlayer
	waitmovement 0
	return

Route24_EventScript_RocketMotionToPlayer::
	applymovement LOCALID_ROCKET, Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

Route24_EventScript_NoRoomForNuggetTrigger::
	msgbox Route24_Text_YouDontHaveAnyRoom
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route24_Movement_WalkDown
	waitmovement 0
	compare VAR_TEMP_1, 0
	call_if_eq Route24_EventScript_RocketWalkBackToPos
	release
	end

Route24_EventScript_RocketWalkBackToPos::
	applymovement LOCALID_ROCKET, Route24_Movement_RocketWalkBackToPos
	waitmovement 0
	return

Route24_Movement_RocketApproachPlayer::
	walk_left
	step_end

Route24_Movement_RocketWalkBackToPos::
	walk_right
	walk_in_place_fastest_left
	step_end

Route24_Movement_WalkDown::
	walk_down
	step_end

Route24_EventScript_Damian::
	lock
	faceplayer
	goto_if_set FLAG_GOT_CHARMANDER, Route24_EventScript_HowsCharmander
	msgbox Route24_Text_CharmanderTrainer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route24_EventScript_ReceiveCharmander
	compare VAR_RESULT, NO
	goto_if_eq Route24_EventScript_CharmanderDeclined
	releaseall
	end

Route24_EventScript_CharmanderDeclined::
	msgbox Route24_Text_CharmanderDeclined
	releaseall
	end

Route24_EventScript_HowsCharmander::
	msgbox Route24_Text_HowsCharmander
	releaseall
	end

Route24_EventScript_ReceiveCharmander::
	setvar VAR_TEMP_1, SPECIES_CHARMANDER
	givemon SPECIES_CHARMANDER, 15, ITEM_CHARCOAL
	compare VAR_RESULT, 0
	goto_if_eq Route24_EventScript_ReceiveCharmanderParty
	compare VAR_RESULT, 1
	goto_if_eq Route24_EventScript_ReceiveCharmanderPC
	compare VAR_RESULT, 2
	goto_if_eq EventScript_NoMoreRoomForPokemon
	release
	end

Route24_EventScript_ReceiveCharmanderParty:: @ 8161B12
	textcolor 3
	playfanfare MUS_LEVEL_UP
	message Route24_Text_ObtainedCharmanderFromDamian
	waitmessage
	waitfanfare
	getspeciesname 0, SPECIES_CHARMANDER
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route24_EventScript_EndReceiveCharmander
	call EventScript_GetGiftMonPartySlot
	call EventScript_ChangePokemonNickname
	goto Route24_EventScript_EndReceiveCharmander
	end

Route24_EventScript_ReceiveCharmanderPC:: @ 8161B45
	textcolor 3
	playfanfare MUS_LEVEL_UP
	message Route24_Text_ObtainedCharmanderFromDamian
	waitmessage
	waitfanfare
	getspeciesname 0, SPECIES_CHARMANDER
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route24_EventScript_CharmanderTransferredToPC
	call EventScript_NameReceivedBoxMon
	goto Route24_EventScript_CharmanderTransferredToPC
	end

Route24_EventScript_CharmanderTransferredToPC:: @ 8161B73
	call EventScript_TransferredToPC
	goto Route24_EventScript_EndReceiveCharmander
	end

Route24_EventScript_EndReceiveCharmander:: @ 8161B7E
	setflag FLAG_GOT_CHARMANDER
	release
	end
