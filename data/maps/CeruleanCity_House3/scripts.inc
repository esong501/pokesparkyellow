CeruleanCity_House3_MapScripts:: @ 816A9A7
	.byte 0

CeruleanCity_House3_EventScript_OldWoman:: @ 816A9A8
	msgbox CeruleanCity_House3_Text_PleaseTradeWithMyHusband, MSGBOX_NPC
	end

CeruleanCity_House3_EventScript_Dontae:: @ 816A9B1
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_JYNX
	call EventScript_GetInGameTradeSpeciesInfo
	goto_if_set FLAG_DID_ZYNX_TRADE, CeruleanCity_House3_EventScript_AlreadyTraded
	msgbox Trade_Text_DoYouHaveMonWouldYouTradeForMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeruleanCity_House3_EventScript_DeclineTrade
	call EventScript_ChooseMonForInGameTrade
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge CeruleanCity_House3_EventScript_DeclineTrade
	call EventScript_GetInGameTradeSpecies
	compare VAR_RESULT, VAR_0x8009
	goto_if_ne CeruleanCity_House3_EventScript_NotRequestedMon
	call EventScript_DoInGameTrade
	msgbox Trade_Text_Thanks
	setflag FLAG_DID_ZYNX_TRADE
	release
	end

CeruleanCity_House3_EventScript_Melanie::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BULBASAUR, CeruleanCity_House3_EventScript_HowsBulbasaur
	msgbox CeruleanCity_House3_Text_BulbasaurTrainer
	goto_if_set FLAG_BADGE01_GET, CeruleanCity_House3_EventScript_MelanieBadge
	releaseall
	end

CeruleanCity_House3_EventScript_MelanieBadge::
	msgbox CeruleanCity_House3_Text_BadgeGet, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CeruleanCity_House3_EventScript_ReceiveBulbasaur
	compare VAR_RESULT, NO
	goto_if_eq CeruleanCity_House3_EventScript_BulbasaurDeclined
	end

CeruleanCity_House3_EventScript_BulbasaurDeclined::
	msgbox CeruleanCity_House3_Text_BulbasaurDeclined
	releaseall
	end

CeruleanCity_House3_EventScript_HowsBulbasaur::
	msgbox CeruleanCity_House3_Text_HowsBulbasaur
	releaseall
	end

CeruleanCity_House3_EventScript_ReceiveBulbasaur::
	setvar VAR_TEMP_1, SPECIES_BULBASAUR
	givemon SPECIES_BULBASAUR, 12, ITEM_MIRACLE_SEED
	compare VAR_RESULT, 0
	goto_if_eq CeruleanCity_House3_EventScript_ReceiveBulbasaurParty
	compare VAR_RESULT, 1
	goto_if_eq CeruleanCity_House3_EventScript_ReceiveBulbasaurPC
	compare VAR_RESULT, 2
	goto_if_eq EventScript_NoMoreRoomForPokemon
	release
	end

CeruleanCity_House3_EventScript_ReceiveBulbasaurParty:: @ 8161B12
	textcolor 3
	playfanfare MUS_LEVEL_UP
	message CeruleanCity_House3_Text_ObtainedBulbasaurFromMelanie
	waitmessage
	waitfanfare
	getspeciesname 0, SPECIES_BULBASAUR
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeruleanCity_House3_EventScript_EndReceiveBulbasaur
	call EventScript_GetGiftMonPartySlot
	call EventScript_ChangePokemonNickname
	goto CeruleanCity_House3_EventScript_EndReceiveBulbasaur
	end

CeruleanCity_House3_EventScript_ReceiveBulbasaurPC:: @ 8161B45
	textcolor 3
	playfanfare MUS_LEVEL_UP
	message CeruleanCity_House3_Text_ObtainedBulbasaurFromMelanie
	waitmessage
	waitfanfare
	getspeciesname 0, SPECIES_BULBASAUR
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeruleanCity_House3_EventScript_BulbasaurTransferredToPC
	call EventScript_NameReceivedBoxMon
	goto CeruleanCity_House3_EventScript_BulbasaurTransferredToPC
	end

CeruleanCity_House3_EventScript_BulbasaurTransferredToPC:: @ 8161B73
	call EventScript_TransferredToPC
	goto CeruleanCity_House3_EventScript_EndReceiveBulbasaur
	end

CeruleanCity_House3_EventScript_EndReceiveBulbasaur:: @ 8161B7E
	setflag FLAG_GOT_BULBASAUR
	release
	end

CeruleanCity_House3_EventScript_DeclineTrade:: @ 816AA0B
	msgbox Trade_Text_WellIfYouDontWantTo
	release
	end

CeruleanCity_House3_EventScript_NotRequestedMon:: @ 816AA15
	getspeciesname 0, VAR_0x8009
	msgbox Trade_Text_ThisIsntMon
	release
	end

CeruleanCity_House3_EventScript_AlreadyTraded:: @ 816AA23
	msgbox Trade_Text_HasTradedMonGrownStronger
	release
	end
