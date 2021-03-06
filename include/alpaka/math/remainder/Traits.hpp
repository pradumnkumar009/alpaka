/* Copyright 2019 Benjamin Worpitz
 *
 * This file is part of Alpaka.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */


#pragma once

#include <alpaka/meta/IsStrictBase.hpp>

#include <alpaka/core/Common.hpp>

#include <boost/config.hpp>

#include <type_traits>

namespace alpaka
{
    namespace math
    {
        namespace traits
        {
            //#############################################################################
            //! The remainder trait.
            template<
                typename T,
                typename Tx,
                typename Ty,
                typename TSfinae = void>
            struct Remainder;
        }

        //-----------------------------------------------------------------------------
        //! Computes the IEEE remainder of the floating point division operation x/y.
        //!
        //! \tparam T The type of the object specializing Remainder.
        //! \tparam Tx The type of the first argument.
        //! \tparam Ty The type of the second argument.
        //! \param remainder The object specializing Max.
        //! \param x The first argument.
        //! \param y The second argument.
        ALPAKA_NO_HOST_ACC_WARNING
        template<
            typename T,
            typename Tx,
            typename Ty>
        ALPAKA_FN_HOST_ACC auto remainder(
            T const & remainder,
            Tx const & x,
            Ty const & y)
#ifdef BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
        -> decltype(
            traits::Remainder<
                T,
                Tx,
                Ty>
            ::remainder(
                remainder,
                x,
                y))
#endif
        {
            return
                traits::Remainder<
                    T,
                    Tx,
                    Ty>
                ::remainder(
                    remainder,
                    x,
                    y);
        }

        namespace traits
        {
            //#############################################################################
            //! The Remainder specialization for classes with RemainderBase member type.
            template<
                typename T,
                typename Tx,
                typename Ty>
            struct Remainder<
                T,
                Tx,
                Ty,
                typename std::enable_if<
                    meta::IsStrictBase<
                        typename T::RemainderBase,
                        T
                    >::value
                >::type>
            {
                //-----------------------------------------------------------------------------
                ALPAKA_NO_HOST_ACC_WARNING
                ALPAKA_FN_HOST_ACC static auto remainder(
                    T const & remainder,
                    Tx const & x,
                    Ty const & y)
#ifdef BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
                -> decltype(
                    math::remainder(
                        static_cast<typename T::RemainderBase const &>(remainder),
                        x,
                        y))
#endif
                {
                    // Delegate the call to the base class.
                    return
                        math::remainder(
                            static_cast<typename T::RemainderBase const &>(remainder),
                            x,
                            y);
                }
            };
        }
    }
}
