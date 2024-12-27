#ifndef __RENALIBS_RENARICH_EXCEPTIONOS_H__
#define __RENALIBS_RENARICH_EXCEPTIONOS_H__

#include<exception>
#include<sstream>
#include<string>

#define RENARICH_ADD_NEW_EXCEPTION( ex_name )                                                       \
    class ex_name : public renarich_basic_exception<ex_name> {                                      \
                                                                                                    \
        public:                                                                                     \
            ex_name( unsigned int __ui_errcode , const std::string& __c_s_errmsg )                  \
                : renarich_basic_exception<ex_name>( __ui_errcode , __c_s_errmsg ) {}               \
            virtual ~ex_name() noexcept {}                                                          \
                                                                                                    \
            static constexpr const char* get_exception_type_name() noexcept { return #ex_name; }    \
    }

namespace rena::exceptions {

    template<typename T>
    class renarich_basic_exception : public std::exception {

        public:
            renarich_basic_exception( unsigned int __ui_errcode , const std::string& __c_s_errmsg ) : _ui_errcode( __ui_errcode ) {
                std::ostringstream oss;
                oss << "[" << T::get_exception_type_name() << ":" << this -> _ui_errcode << "] " << __c_s_errmsg;
                this -> _s_errmsg = oss.str();
                return;
            }
            virtual ~renarich_basic_exception() noexcept {}

            virtual const char* what() const noexcept {
                return this -> _s_errmsg.c_str();
            };

            unsigned int code() const noexcept {
                return this -> _ui_errcode;
            }

        private:
            unsigned int _ui_errcode;
            std::string _s_errmsg;

    }; // class renarich_basic_exception

    RENARICH_ADD_NEW_EXCEPTION( renarich_illegal_value );
    RENARICH_ADD_NEW_EXCEPTION( renarich_unexpected );

} // namespace rena::exceptions

#endif // __RENALIBS_RENARICH_EXCEPTIONOS_H__
