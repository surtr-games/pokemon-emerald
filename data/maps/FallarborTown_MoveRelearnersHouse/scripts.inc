.set LOCALID_MOVE_RELEARNER, 1
.set LOCALID_EV_TRAINER, 2

FallarborTown_MoveRelearnersHouse_MapScripts::
	.byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor:
	.string "I'm the MOVE TUTOR.\p"
	.string "I know all the moves that POKéMON\n"
	.string "learn--every one of them--and I can\l"
	.string "teach POKéMON those moves.\p"
	.string "I can teach a move to a POKéMON\n"
	.string "of yours if you'd like.\p"
	.string "I'll do it for a HEART SCALE.\n"
	.string "I'm collecting those now.$"

FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh! That's it! That's an honest to\n"
	.string "goodness HEART SCALE!\p"
	.string "Let me guess, you want me to teach\n"
	.string "a move?$"

FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon:
	.string "Which POKéMON needs tutoring?$"

FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove:
	.string "Which move should I teach?$"

FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon:
	.string "Sorry…\p"
	.string "It doesn't appear as if I have any move\n"
	.string "I can teach that POKéMON.$"

FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale:
	.string "{PLAYER} handed over one HEART SCALE\n"
	.string "in exchange.$"

FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale:
	.string "If your POKéMON need to learn a move,\n"
	.string "come back with a HEART SCALE.$"

FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg:
	.string "Hunh? There isn't a single move that\n"
	.string "I can teach an EGG.$"

// -------------------------------------------------------------------------------------

FallarborTown_MoveRelearnersHouse_EventScript_EVTrainer::
	lockall
	applymovement LOCALID_EV_TRAINER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_2, FallarborTown_MoveRelearnersHouse_EventScript_AskTrainEVs
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheEVTrainer, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTrainEVs
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskTrainEVs::
	checkitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithEvTrainingItem
	msgbox FallarborTown_MoveRelearnersHouse_Text_PlayerHasEvTrainingItem, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithEvTrainingItem
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMonForEvTraining
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMonForEvTraining::
	msgbox FallarborTown_MoveRelearnersHouse_Text_EvTrainWhichMon, MSGBOX_DEFAULT
	special ChooseMonForEvTraining
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithEvTrainingItem
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_CantEvTrainEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_MoveRelearnersHouse_EventScript_NoEvsToDistribute
	goto FallarborTown_MoveRelearnersHouse_EventScript_OpenEvTrainingMenu
	end

FallarborTown_MoveRelearnersHouse_EventScript_OpenEvTrainingMenu::
	msgbox FallarborTown_MoveRelearnersHouse_Text_HowToTrainMonEvs, MSGBOX_DEFAULT
	special OpenEvEditorFromScript
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMonForEvTraining
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverEvTrainingItem, MSGBOX_DEFAULT
	removeitem ITEM_BIG_PEARL
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithEvTrainingItem
	end

FallarborTown_MoveRelearnersHouse_EventScript_NoEvsToDistribute::
	msgbox FallarborTown_MoveRelearnersHouse_Text_NoEvsToDistribute, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMonForEvTraining
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantEvTrainEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantEvTrainEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMonForEvTraining
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithEvTrainingItem::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithEvTrainingItem, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheEVTrainer:
	.string "I'm the EV TRAINER.$"

FallarborTown_MoveRelearnersHouse_Text_PlayerHasEvTrainingItem:
	.string "You have a BIG PEARL!$"

FallarborTown_MoveRelearnersHouse_Text_EvTrainWhichMon:
	.string "Which POKéMON needs EV training?$"

FallarborTown_MoveRelearnersHouse_Text_HowToTrainMonEvs:
	.string "How should I train your POKéMON?$"

FallarborTown_MoveRelearnersHouse_Text_NoEvsToDistribute:
	.string "Sorry…\p"
	.string "Your POKéMON does not have any EVs.$"

FallarborTown_MoveRelearnersHouse_Text_HandedOverEvTrainingItem:
	.string "{PLAYER} handed over one BIG PEARL\n"
	.string "in exchange.$"

FallarborTown_MoveRelearnersHouse_Text_ComeBackWithEvTrainingItem:
	.string "If your POKéMON need to train EVs,\n"
	.string "come back with a BIG PEARL.$"

FallarborTown_MoveRelearnersHouse_Text_CantEvTrainEgg:
	.string "I cannot train an EGG.$"
