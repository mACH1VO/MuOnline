#pragma once
#include "stdafx.h"

//namespace Global
//{
#define RENDER_QUEUE_INVENTORY_ITEM			RENDER_QUEUE_OVERLAY + 1

	enum ActorType
	{
		Invalid_Actor = 0,
		Monster = 1,
		Gizmo = 2,
		ClientEffect = 3,
		ServerProp = 4,
		Enviroment = 5,
		Critter = 6,
		Player = 7,
		Item = 8,
		AxeSymbol = 9,
		Projectile = 10,
		CustomBrain = 11,
		NPC = 12,
		VisualPlayer = 13
	};

	enum RotationAxis
	{
		yaw__y,
		pitch__x,
		roll__z,
	};

	enum PlayerState
	{
		Idle = 1,
		Walking = 2,
		Attacking = 3,
		Busy = 4,
		Death = 5,
	};
	enum ClassType
	{
		Wizard = 1,
		DK = 2,
		Elf = 3,
		MG = 4,
		DL = 5,
		Summoner = 6,
	};

	enum QueryFlags
	{
		
		NAVMESH_MASK = 1u<<1,
		OBSTACLE_MASK= 1u<<2,

		ACTOR_MASK = 1u<<3,
		ITEM_MASK = 1u<<4,
		MONSTER_MASK = 1u<<5,
		PLAYER_MASK = 1u<<6,
		NPC_MASK = 1u<<7,

		TERRAIN_MASK = 1u<<8,
		DEFAULT_MASK = 1u<<9,
	};

	enum AttributeEncoding
	{
		Int,
		IntMinMax,
		Float16,
		Float16Or32,
		Float32,
	};

	enum AttributeOpcode
	{
		Axe_Bad_Data = 0,
		Attribute_Timer = 1,
		Attribute_Pool = 2,

		Strength = 10,
		Dexterity = 11,
		Intelligence = 12,
		Vitality = 13,

		Strength_Requeriment = 18,
		Dexterity_Requeriment = 19,
		Intelligence_Requeriment = 20,
		Vitality_Requeriment = 21,

		Attack = 31,
		Precision = 32,
		Defense = 33,

		Experience_Granted = 56,
		Experience_Next = 55,

		Level = 59,
		Level_Requeriment = 60,

		Skill = 89,

		Hitpoints_Cur = 103,
		Hitpoints_Max = 110,

		Mana_Cur = 120,
		Mana_Max = 121,

		Speed = 152,

		Damage_Weapon_Max = 177,
		Damage_Weapon_Min = 183,

		AvailableStatsPoints = 229,

		Durability_Cur = 292,
		Durability_Max = 293,

		Item_Quality_Level = 295, // ;)

		DPS = 498,

		Buff_Icon_Count0 = 577,
		Buff_Icon_Count1 = 578,
		Buff_Icon_Count2 = 579,
		Buff_Icon_Count3 = 580,
		Buff_Icon_Count4 = 581,
		Buff_Icon_Count5 = 582,
		Buff_Icon_Count6 = 583,
		Buff_Icon_Count7 = 584,

		
	};

	enum AttributeType
	{
		Integer = 1,
		Float = 2,
		Boolean = 3,
	};

	enum Consumers
	{
		None = 1,
		attribute_,
		ClientManager,
		Game_,
		Factory,
		Inventory,
		__Chat,
		Player_,
		SelectedNPC,
		Effect,
		Login,
		Map,
	};

	enum SkillSlot
	{
		Invalid_slot = -1,
		Primary = 1,
		Secondary = 2,
		_one = 3,
		_two = 4,
		_three = 5,
		_four = 6,
	};

	enum SkillOpcode
	{
		Invalid = -1,

		Hand = 0,

		//DK
		Uppercut = 1,
		Cyclone = 2,
		Lunge = 3,
		Slash = 4,
		FallingSlash = 5,
		Raid = 6,
		Impale = 7,
		Twisting = 8,
		Inner = 9,
		DeathStab = 10,
		RagefulBlow = 11,
		Strike_of_Destruction = 12,
		Combo = 13, 
		CrescentMoonSlash = 14,
		BloodStorm = 15,
		Defense_ = 16,

		//DW
		EnergyBall = 101,
		FireBall = 102,
		PowerWave = 103,
		Lightning = 104,
		Teleport = 105,
		Meteorite = 106,
		Ice = 107,
		Poison = 108,
		Flame = 109,
		Twister = 110,
		EvilSpirits = 111,
		Hellfire = 112,
		AquaBeam = 103,
		Cometfall = 114,
		Inferno = 115,
		TeleportAlly = 116,
		SoulBarrier = 117,
		IceStorm = 118,
		Decay = 119,
		Nova = 120,
	};

	enum StatType
	{
		Strength_ = 0,
		Agility_ = 1,
		Stamina_ = 2,
		Energy_ = 3,
	};

	enum Opcodes
	{
		TryConsoleCommand1 = 1,
		TryConsoleCommand2 = 2,
		QuitGameMessage = 3, // len: 	12
		CreateBNetGameMessage = 4, // len: 	88
		CreateBNetGameResultMessage = 5, // len: 	40
		DWordDataMessage1 = 6, // len: 	12
		RequestJoinBNetGameMessage = 8, // len: 	56
		BNetJoinGameRequestResultMessage = 9, // len: 	72
		JoinBNetGameMessage = 10, // len: 	80
		JoinLANGameMessage = 11, // len: 	196
		VersionsMessage = 13, // len: 	48
		GenericBlobMessage1 = 14, // len:
		NetworkAddressMessage = 15, // len: 	16
		GameIdMessage = 17, // len: 	32
		UInt64DataMessage = 18, // len: 	16
		IntDataMessage1 = 20, // len: 	12
		EntityIdMessage = 22, // len: 	24
		CreateHeroMessage = 23, // len: 	68
		CreateHeroResultMessage = 24, // len: 	32
		SimpleMessage1 = 25, // len: 	8
		BlizzconCVarsMessage = 26, // len: 	20
		SimpleMessage2 = 27, // len: 	8
		GenericBlobMessage2 = 28, // len:
		GenericBlobMessage3 = 29, // len:
		GenericBlobMessage4 = 30, // len:
		GenericBlobMessage5 = 31, // len:
		OpenArtisanWindowMessage = 32, // len: 	12 former ANNDataMessage1
		ArtisanWindowClosedMessage = 33, // len: 	8 former SimpleMessage3
		OpenTradeWindow = 34, // len: 	12          former ANNDataMessage2
		InventoryRequestBuyItemMessage = 35, // len: 	12, former ANNDataMessage3
		InventoryRequestSellItemMessage = 36, // len: 	12, former ANNDataMessage4
		SimpleMessage3 = 37, // len: 	8
		LogoutContextMessage1 = 38, // len: 	16
		LogoutTickTimeMessage = 39, // len: 	20
		LogoutComplete = 40, // len: 	8 formor SimpleMessage4
		LogoutContextMessage2 = 41, // len: 	16
		PlayerIndexMessage1 = 42, // len: 	12
		PlayerIndexMessage2 = 43, // len: 	12
		SimpleMessage5 = 44, // len: 	8
		SimpleMessage6 = 45, // len: 	8
		TutorialMessage = 46, //len:    former GenericBlobMessage6
		GenericBlobMessage15 = 47, //len:  added 8058
		Message = 48, //len: 36
		SimpleMessage48 = 49, //Len: 8  added 8058
		ConnectionEstablishedMessage = 50, // len: 	20
		GameSetupMessage = 51, // len: 	20
		GameSetupMessageAck = 52, // len: 	8 former SimpleMessage7
		NewPlayerMessage = 53, // len: 	16916
		PlayerKickTimerMessage = 54, //len: 16
		PlayerBannerMessage = 55, // len: 	former GenericBlobMessage7
		EnterWorldMessage = 56, // len: 	28
		RevealSceneMessage = 57, // len: 	1292
		DestroySceneMessage = 58, // len: 	16
		SwapSceneMessage = 59, // len: 	20
		RevealWorldMessage = 60, // len: 	16
		RevealTeamMessage = 61, // len: 	20
		PlayerActorSetInitialMessage = 62, // len: 	16
		HeroStateMessage = 63, // len: 	16652
		ACDCreateActorMessage = 64, // len: 	132
		ACDDestroyActorMessage = 65, // len: 	12 former ANNDataMessage6
		PlayerEnterKnownMessage = 66, // len: 	16
		ACDEnterMapMessage = 67, // len: 	12 former ANNDataMessage7
		ACDWorldPositionMessage = 68, // len: 	48
		InventoryResponseMoveMessage = 69, // len: 	32
		ACDInventoryUpdateActorSNO = 70, // len: 	16
		TrickleMessage = 71, // len: 	116
		DeleteBuffIconMessage = 72, // len: 	12
		MapRevealSceneMessage = 73, // len: 	52
		SavePointInfoMessage = 74, // len: 	12
		HearthPortalInfoMessage = 75, // len: 	16
		ReturnPointInfoMessage = 76, // len: 	12
		AffixMessage = 77, // len: 	148
		RareMonsterNamesMessage = 78, // len: 	52
		RareItemNameMessage = 79, // len: 	28
		PortalSpecifierMessage = 80, // len: 	24
		AttributeSetValueMessage = 81, // len: 	28
		AttributesSetValuesMessage = 82, // len: 	256
		VisualEquipmentMessage = 83, // len: 	140
		ProjectileStickMessage = 84, // len: 	28
		TargetMessage = 85, // len: 	60
		SecondaryAnimationPowerMessage = 86, // len: 	28
		LoopingAnimationPowerMessage = 87, // len:  20
		DWordDataMessage2 = 88, // len: 	12
		DWordDataMessage3 = 89, // len: 	12
		DWordDataMessage4 = 90, // len: 	12
		DWordDataMessage5 = 91, // len: 	12
		TryChatMessage = 92, // len: 	528
		ChatMessage = 93, // len: 	528
		InventoryDropItemMessage = 94, // len: 	12 former ANNDataMessage9
		InventoryRequestMoveMessage = 95, // len: 	28
		InventoryRequestQuickMoveMessage = 96, // len:  28
		InventoryRequestSocketMessage = 97, // len: 	16
		CreateInventoryItemMessage = 98, // len: 	28
		DestroyInventoryItemMessage = 99, // len: 	40
		InventoryDropStackPortionMessage = 100, //len:   24
		InventoryShowWindowMessage = 101, // len: 	24
		InventoryCloseWindowMessage = 102, // len: 	12
		InventoryRequestJewelUse = 103, //len: 12 former ANNDataMessageXX
		SimpleMessage47 = 104, //len 8 added in 7841
		ANNDataMessage11 = 105, // len: 	12
		InventoryRequestUseMessage = 106, // len: 	36
		HelperDetachMessage = 107, // len: 	12
		AssignSkillMessage1 = 108, // len: 	16
		UnassignSkillMessage = 109, //len: 12
		AssignTraitsMessage = 110, // len: 20 added patch 13
		AssignSkillMessage2 = 111, // len: 	16
		AssignSkillMessage3 = 112, // len: 	16
		HirelingRequestLearnSkillMessage = 113, // len: 	20
		HotbarButtonData = 114, // len: 	12 former ANNDataMessage12
		AssignStatMessage = 115, // len: 12 added patch 13
		IntDataMessage2 = 116, // len: 	12
		PlayAnimationMessage = 117, // len: 	72
		ANNDataMessage13 = 118, // len: 	12
		ACDTranslateNormalMessage = 119, // len: 	76 former ACDTranslateNormalMessage1
		ACDTranslateSnappedMessage = 120, // len: 	36
		ACDTranslateFacingMessage = 121, // len: 	20
		ACDTranslateFixedMessage = 122, // len: 	36
		ACDTranslateArcMessage = 123, // len: 	60
		ACDTranslateDetPathMessage = 124, // len: 	88
		ACDTranslateDetPathSinMessage = 125, // len: 	104
		ACDTranslateDetPathSpiralMessage = 126, // len: 	72
		ACDTranslateSyncMessage = 127, // len: 	32
		ACDTranslateFixedUpdateMessage = 128, // len: 	36
		ACDClientTranslateMessage = 129, //len: 44 (Added patch 8)
		PlayerTranslateFacingMessage = 130, // len: 	20 former ACDTranslateFacingMessage2
		ACDTranslateAckMessage = 131, //len: 12
		PlayEffectMessage = 132, // len: 	24
		PlayHitEffectMessage = 133, // len: 	24
		PlayHitEffectOverrideMessage = 134, // len: 	20
		PlayNonPositionalSoundMessage = 135, // len: 	12
		PlayErrorSoundMessage = 136, // len: 	12
		PlayMusicMessage = 137, // len: 	12
		SimpleMessage4 = 138,  // len: 	8
		PlayCutsceneMessage = 139, // len: 	12
		ComplexEffectAddMessage = 140, // len: 	36
		FlippyMessage = 141, // len: 	32
		WaypointActivatedMessage = 142, // len: 	20
		OpenWaypointSelectionWindowMessage = 143, // len: 	12 former ANNDataMessage14
		ANNDataMessage15 = 144, // len: 	12
		ANNDataMessage16 = 145, // len: 	12
		SimpleMessage49 = 146, // len: 8 added patch 13
		AimTargetMessage = 147, // len: 	36
		ACDChangeGBHandleMessage = 148, // len: 	20
		GameTickMessage = 149, // len: 	12  former DWordDataMessage6
		DataIDDataMessage1 = 150, // len: 	12
		DataIDDataMessage2 = 151, // len: 	12
		EndOfTickMessage = 152, // len: 	16
		TryWaypointMessage = 153, // len: 	16
		NPCInteractOptionsMessage = 154, // len: 	340
		ANNDataMessage17 = 155, // len: 	12
		ANNDataMessage18 = 156, // len: 	12
		SimpleMessage8 = 157, // len: 	8
		QuestUpdateMessage = 158, // len: 	28
		QuestMeterMessage = 159, // len: 	20
		QuestCounterMessage = 160, // len: 	20
		QuestStepCompleteMessage = 161, // len:  // former GenericBlobMessage8
		PlayerIndexMessage3 = 162, // len: 	12
		PlayerLevel = 163, // len: 	16
		OpenSharedStashMessage = 164, // len: 	12, former ANNDataMessage19
		ACDPickupFailedMessage = 165, // len: 	16
		PetMessage = 166, // len: 	24
		PetDetachMessage = 167, // len: 16
		HirelingInfoUpdateMessage = 168, // len: 	24
		UIElementMessage = 169, // len: 	16
		PlayerBusyMessage = 170, // len: 	12      //  former: BoolDataMessage1
		TradeMessage1 = 171, // len: 	56
		TradeMessage2 = 172, // len: 	56
		PlayerIndexMessage4 = 173, // len: 	12
		SimpleMessage10 = 174, // len: 	8
		PlayerIndexMessage5 = 175, // len: 	12
		SetIdleAnimationMessage = 176, // len: 	16
		ACDCollFlagsMessage = 177, // len: 	16
		GoldModifiedMessage = 178, // len: 	12
		ActTransitionMessage = 179, // len: 	16
		InterstitialMessage = 180, // len: 	16
		EffectGroupACDToACDMessage = 181, // len: 	20
		RopeEffectMessageACDToACD = 182, // len: 	28
		RopeEffectMessageACDToPlace = 183, // len: 	36
		ANNDataMessage21 = 184, // len: 	12
		ShrineActivatedMessage = 185, // len: 	12   former ANNDataMessage22
		GameSyncedDataMessage = 186, // len: 	96
		ACDChangeActorMessage = 187, // len: 	16
		PlayerWarpedMessage = 188, // len: 	16
		VictimMessage = 189, // len: 	48
		KillCountMessage = 190, // len: 	24
		WorldStatusMessage = 191, // len: 	16
		WeatherOverrideMessage = 192, // len: 	16
		SimpleMessage11 = 193, // len: 	8
		ACDShearMessage = 194, // len: 	16
		ACDChangeActorVisibility = 195, // len: 	20
		HeartbeatMessage = 196, // len: 	8 former SimpleMessage12
		PlayConvLineMessage = 197, // len: 	172
		StopConvLineMessage = 198, // len: 	16
		AdvanceConvMessage = 199, //len : 16
		UpdateConvAutoAdvanceMessage = 200, // len: 20
		RequestCloseConversationWindowMessage = 201, // len: 	8 former SimpleMessage13
		EndConversationMessage = 202, // len: 	20
		SNODataMessage2 = 203, // len: 	12
		FinishConversationMessage = 204, // len: 	12 former SNODataMessage3
		HirelingSwapMessage1 = 205, // len: 	12
		HirelingSwapMessage2 = 206, // len: 	12
		SimpleMessage14 = 207, // len: 	8
		DeathFadeTimeMessage = 208, // len: 	24
		ANNDataMessage23 = 209, // len: 	12
		ANNDataMessage24 = 210, // len: 	12
		DisplayGameTextMessage = 211, // len: 	536
		IntDataMessage4 = 212, // len: 	12
		DWordDataMessage7 = 213, // len: 	12
		GBIDDataMessage1 = 214, // len: 	12
		ANNDataMessage25 = 215, // len: 	12
		ANNDataMessage26 = 216, // len: 	12
		ACDLookAtMessage = 217, // len: 	16
		KillCounterUpdateMessage = 218, // len: 	24
		LowHealthCombatMessage = 219, // len: 	16
		AddBuffIconMessage = 220, // len: 	16
		FloatingNumberMessage = 221, // len: 	20
		FloatingAmountMessage = 222, // len: 	40
		RemoveRagdollMessage = 223, // len: 	16
		SNONameDataMessage = 224, // len: 	16
		LoreMessage = 225, // len: 	16
		DWordDataMessage12 = 228, // len: 12 added 8059
		WorldDeletedMessage = 229, // len: 	12
		SimpleMessage16 = 230, // len: 	8
		IntDataMessage5 = 231, // len: 	12
		TimedEventStartedMessage = 232, // len: 	20
		SNODataMessage4 = 233, // len: 	12
		ActTransitionStartedMessage = 234, // len: 	16
		SimpleMessage17 = 235, // len: 	8 //added in 7728
		RequestBuySharedStashSlotsMessage = 236, // len: 	8   former SimpleMessage17
		PlayerQuestMessage1 = 237, // len: 	16
		PlayerQuestMessage2 = 238, // len: 	16
		PlayerDeSyncSnapMessage = 239, // len: 	28
		RequestUseNephalemCubeMessage = 240, // len: 	12  former ANNDataMessage27
		SalvageResultsMessage = 241, // len: 	60
		SimpleMessage18 = 242, // len: 	8
		MapMarkerInfoMessage = 243, // len: 	72
		BlacksmithDataProgressMessage = 244, // len: 	   former GenericBlobMessage9
		JewelerDataProgressMessage = 245, // len: 	   former GenericBlobMessage10
		MysticDataProgressMessage = 246, // len: 	former GenericBlobMessage11
		BlacksmithDataInitialMessage = 247, // len:   former genericBlobMessage 12
		JewelerDataInitialMessage = 248, // len: 	former GenericBlobMessage13
		MysticDataInitialMessage = 249, // len: 	former GenericBlobMessage14
		ANNDataMessage28 = 250, // len: 	12
		DebugActorTooltipMessage = 251, // len: 	524
		BossEncounterMessage1 = 252, // len: 	16
		SimpleMessage20 = 253, // len: 	8
		SimpleMessage21 = 254, // len: 	8
		BossEncounterMessage2 = 255, // len: 	16
		SimpleMessage22 = 256, // len: 	8
		SimpleMessage23 = 257, // len: 	8
		EncounterInviteStateMessage = 258, // len: 	12
		SkillListMessage = 259, // len: 	8
		AvailableSkillListMessage = 260, // len: 	8
		IntDataMessage3 = 261, // len: 12 added 8059
		SimpleMessage26 = 262, // len: 	8
		SimpleMessage27 = 263, // len: 	8
		SimpleMessage28 = 264, // len: 	8
		SimpleMessage29 = 265, // len: 	8
		CameraFocusMessage = 266, // len: 	20
		CameraZoomMessage = 267, // len: 	20
		CameraYawMessage = 268, // len: 	20
		SimpleMessage30 = 269, // len: 	8
		BoolDataMessage2 = 270, // len: 	12
		SimpleMessage50 = 271, // len: 8 added patch 13
		BossZoomMessage = 272, // len: 	16
		EnchantItemMessage = 273, // len: 	16
		ANNDataMessage29 = 274, // len: 	12
		RepairAllMessage = 275, // len: 	8 former SimpleMessage31
		RepairEquippedMessage = 276, // len: 	8 former SimpleMessage32
		RequestTrainArtisanMessage = 277, // len: 	8   former SimpleMessage33
		IntDataMessage6 = 278, // len: 	12
		DebugDrawPrimMessage = 279, // len: 	188
		GBIDDataMessage2 = 280, // len: 	12
		CraftingResultsMessage = 281, // len: 	20
		CrafterLevelUpMessage = 282, // len: 	20
		ANNDataMessage31 = 283, // len: 	12
		ANNDataMessage32 = 284, // len: 	12
		IntDataMessage7 = 285, // len: 	12
		UnlockDifficultyMessage = 286, // len:  16 added patch 13
		IntDataMessage8 = 287, // len: 	12
		HirelingRetrainMessage = 288, // len: 	8 former SimpleMessage35
		SimpleMessage36 = 289, // len: 	8
		GameChangeSceneMessage = 290, // len: 	16
		SimpleMessage37 = 291, // len: 	8
		TutorialShownMessage = 292, // len: 	12 former SNODataMessage5
		RequestBuffCancelMessage = 293, // len: 	16
		CancelCinematicsMessage = 294, // len: 	8 fomer Simplemessage38
		PlayerIndexMessage7 = 295, // len: 	12
		SimpleMessage39 = 296, // len: 	8
		SimpleMessage40 = 297, // len: 	8
		DWordDataMessage8 = 298, // len: 	12
		DWordDataMessage9 = 299, // len: 	12
		DWordDataMessage10 = 300, // len: 	12
		DWordDataMessage11 = 301, // len: 	12
		BroadcastTextMessage = 302, // len: 	520
		LoadCompleteMessage = 303, // len: 	8 former SimpleMessage41
		SimpleMessage42 = 304, // len: 	8
		NPCSelectConversationMessage = 305, // len: 	12 former SNODataMessage6
		HirelingDismissMessage = 306, // len: 	12 former ANNDataMessage33
		CraftInteractionMessage = 307, // len: 	8 former SimpleMessage43
		HirelingHireMessage = 308, // len: 	8 former SimpleMessage44
		HirelingInventoryMessage = 309, // len: 	8 former SimpleMessage45
		SNODataMessage7 = 310, // len:  12
		ActTransitionStartedMessage2 = 311, //len:   16
		VoteKickMessage1 = 312, //len:   528
		PlayerIndexMessage8 = 313, // len: 	12
		PlayerIndexMessage9 = 314, // len: 	12
		VoteKickMessage2 = 315, //len:   528
		BoolDataMessage3 = 316, // len: 	12
		PlayerIndexMessage10 = 317, // len: 	12
		PlayerIndexMessage11 = 318, // len: 	12
		BoolDataMessage4 = 319, // len: 	12
		BoolDataMessage5 = 320, // len: 	12
		SimpleMessage51 = 321, //len: 8 added patch 13
		SimpleMessage52 = 322, //len: 8 added patch 14
		LoginMessage = 323,
		ToonListMessage = 324
	};

	enum BlendingTransition
	{
		BlendSwitch,         // stop source and start dest
		BlendWhileAnimating,   // cross fade, blend source animation out while blending destination animation in
		//BlendThenAnimate      // blend source to first frame of dest, when done, start dest anim
	};

	enum InventoryWindowsID : int
	{
		_PlayerInventory = 1,
		Vault = 2,
		_NPC = 3,
		_SHOP = 4,
	};

	enum EquipmentSlotId
	{
		_Inventory = 0,
		Helm = 1,
		Armor = 2,
		Weapon_L = 3,
		Weapon_R = 4,
		Gloves = 5,
		Necklace = 6,
		Boots = 7,
		Shoulders = 8,
		Pants = 9,
		Bracers = 10,
		Ring_right = 11,
		Ring_left = 12,
		Fairy = 13,
		Skills = 14,
		Stash = 15,
		Gold = 16,
		BackPack = 17,
		Wing = 18
	};

//}
