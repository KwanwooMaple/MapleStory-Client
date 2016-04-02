/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 Daniel Allendorf                                        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Net\PacketHandler.h"
#include "Character\Buffstat.h"

namespace Net
{
	// Parses keymappings and sends them to the Keyboard.
	class KeymapHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};


	// Parses skill macros.
	class SkillMacrosHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};


	// Notifies the client of changes in character stats.
	// Opcode: CHANGE_STATS(31)
	class ChangeStatsHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};


	// Base class for packets which need to parse buffstats.
	class BuffHandler : public PacketHandler
	{
	public:
		void handle(InPacket& recv) const override;

	protected:
		using Buffstat = Character::Buffstat;

		virtual void handlebuff(InPacket& recv, Buffstat::Value buff) const = 0;
	};


	// Notifies the client that a buff was applied to the player.
	// Opcode: GIVE_BUFF(32)
	class ApplyBuffHandler : public BuffHandler
	{
	protected:
		using Buffstat = Character::Buffstat;

		void handlebuff(InPacket& recv, Buffstat::Value buff) const override;
	};


	// Notifies the client that a buff was cancelled.
	// Opcode: CANCEL_BUFF(33)
	class CancelBuffHandler : public BuffHandler
	{
	protected:
		using Buffstat = Character::Buffstat;

		void handlebuff(InPacket& recv, Buffstat::Value buff) const override;
	};


	// Force a stats recalculation.
	// Opcode: RECALCULATE_STATS(35)
	class RecalculateStatsHandler : public PacketHandler
	{
		void handle(InPacket&) const override;
	};


	// Updates the player's skills with the client.
	// Opcode: UPDATE_SKILLS(36)
	class UpdateskillsHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};


	// Notifies the client that a skill is on cooldown.
	// Opcode: ADD_COOLDOWN(234)
	class AddCooldownHandler : public PacketHandler
	{
		void handle(InPacket& recv) const override;
	};
}