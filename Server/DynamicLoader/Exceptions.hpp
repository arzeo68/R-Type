/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Main file for lib leading exceptions
*/

#ifndef OOP_ARCADE_2019_SOLOADER_EXCEPTIONS_HPP_
#define OOP_ARCADE_2019_SOLOADER_EXCEPTIONS_HPP_

#include <string>

namespace SoLoader {
    /**
     * The namespace Exceptions regroup all exceptions related to the SoLoader namespace
     */
    namespace Exceptions {

        /**
         * InvalidSO is an exception throw when the SO library passed as argument cannot be open
         * by `dlopen`. It may be due to several factors, refer to the error message displayed if
         * this occurs.
         */
        class InvalidSO : std::exception {
            public:
                explicit InvalidSO(const std::string &DLLPath) noexcept;
                InvalidSO() = delete;

                /**
                 * Required by std::exception
                 * @return An explicit message explaining why the error occurred.
                 */
                const char *what() const noexcept override;

            private:
                std::string _dllName;
        };

        /**
         * InvalidEntryPoint is an exception throw when the SO library previously doesn't have
         * the entry point specified by SoLoader::SoLoader::ENTRY_POINT_NAME.
         */
        class InvalidEntryPoint : std::exception {
            public:
                explicit InvalidEntryPoint(const std::string &DLLName) noexcept;
                InvalidEntryPoint() = delete;

                /**
                 * Required by std::exception
                 * @return An explicit message explaining why the error occurred.
                 */
                const char *what() const noexcept override;

            private:
                std::string _dllName;
        };
    }
}


#endif //OOP_ARCADE_2019_SOLOADER_EXCEPTIONS_HPP_
