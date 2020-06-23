/*
 *  Created by Phil Nash on 15/6/2018.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_SINGLETONS_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_SINGLETONS_HPP_INCLUDED

namespace Catch {

    struct ISingleton {
        virtual ~ISingleton();
    };


    void addSingleton( ISingleton* singleton );
    void cleanupSingletons();

    template<typename T>
    static T* getStaticSingletonInstance() {
        static T* t = nullptr;
        if( !t ) {
            t = new T;
            addSingleton( t );
        }
        return t;
    }

    template<typename SingletonImplT, typename InterfaceT = SingletonImplT, typename MutableInterfaceT = InterfaceT>
    class Singleton : SingletonImplT, public ISingleton {

        static auto getInternal() -> Singleton* {
            return getStaticSingletonInstance<Singleton>();
        }

    public:
        static auto get() -> InterfaceT const& {
            return *getInternal();
        }
        static auto getMutable() -> MutableInterfaceT& {
            return *getInternal();
        }
    };

} // namespace Catch

#endif // TWOBLUECUBES_CATCH_SINGLETONS_HPP_INCLUDED
