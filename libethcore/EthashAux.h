/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "BlockHeader.h"

#include <libdevcore/Worker.h>

#include <ethash/ethash.hpp>

namespace dev
{
namespace eth
{

struct Result
{
	h256 value;
	h256 mixHash;
};

class EthashAux
{
public:
	static Result eval(int epoch, h256 const& _headerHash, uint64_t  _nonce) noexcept;
};

struct WorkPackage
{
    WorkPackage() = default;
    explicit WorkPackage(BlockHeader const& _bh)
      : boundary(_bh.boundary()),
        header(_bh.hashWithout()),
        epoch(ethash::get_epoch_number(static_cast<int>(_bh.number())))
    {}
    explicit operator bool() const { return header != h256(); }

    h256 boundary;
    h256 header;  ///< When h256() means "pause until notified a new work package is available".
    h256 job;
    int epoch = -1;

    uint64_t startNonce = 0;
    int exSizeBits = -1;
    int job_len = 8;
};

struct Solution
{
	uint64_t nonce;
	h256 mixHash;
	WorkPackage work;
	bool stale;
};

}
}
