/* Copyright 2019 Axel Huebl, Benjamin Worpitz
 *
 * This file is part of Alpaka.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#pragma once

#include <alpaka/math/floor/Traits.hpp>

#include <alpaka/core/Unused.hpp>

#include <type_traits>
#include <cmath>

namespace alpaka
{
    namespace math
    {
        //#############################################################################
        //! The standard library floor.
        class FloorStdLib
        {
        public:
            using FloorBase = FloorStdLib;
        };

        namespace traits
        {
            //#############################################################################
            //! The standard library floor trait specialization.
            template<
                typename TArg>
            struct Floor<
                FloorStdLib,
                TArg,
                typename std::enable_if<
                    std::is_arithmetic<TArg>::value>::type>
            {
                ALPAKA_FN_HOST static auto floor(
                    FloorStdLib const & floor,
                    TArg const & arg)
                -> decltype(std::floor(arg))
                {
                    alpaka::ignore_unused(floor);
                    return std::floor(arg);
                }
            };
        }
    }
}
