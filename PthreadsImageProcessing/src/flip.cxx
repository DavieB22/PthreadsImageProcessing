/**
********************************************************************************
*
*   @file       flip.cxx
*
*   @brief      Flip input image horizonatally or vertically.
*
*   @version    1.0
*
*   @date       17/10/2019
*
*   @author     Franck Vidal
*   @author     YOUR NAME
*
********************************************************************************
*/


//******************************************************************************
//  Include
//******************************************************************************
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <chrono>
#include "Image.h"
#include "PthreadImage.h"

using namespace std;

//******************************************************************************
//  Typedef
//******************************************************************************
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;

//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Return code
    int error_code(0);
	// Timestamps
	timestamp start;
	timestamp end;
	double time_taken;

    // Catch exceptions
    try
    {
		

        if (argc == 4)
        {
            // Declarations
            Image input;
            Image output;

            // Load the image
            input.loadASCII(argv[2]);

            // Flip the image
            if (std::string(argv[1]) == "-H")
            {
				start = chrono::high_resolution_clock::now();

                output = input.flipHorizontally();

				end = chrono::high_resolution_clock::now();
				time_taken = chrono::duration<double>(end - start).count();
				cout << "Serial H flip took: " << time_taken << " Seconds" << endl;
			
            }
            else if (std::string(argv[1]) == "-V")
            {
				start = chrono::high_resolution_clock::now();

                output = input.flipVertically();

				end = chrono::high_resolution_clock::now();
				time_taken = chrono::duration<double>(end - start).count();
				cout << "Serial V flip took: " << time_taken << " Seconds" << endl;
            }
            else
            {
                throw "Invalid option";
            }

            // Save the output
            output.saveASCII(argv[3]);
        }
        else if (argc == 5)
        {
            // Declarations
            PthreadImage input(atoi(argv[4]));
            PthreadImage output;

            // Load the image
            input.loadASCII(argv[2]);

            // Flip the image
            if (std::string(argv[1]) == "-H")
            {
				start = chrono::high_resolution_clock::now();

                output = input.flipHorizontally();

				end = chrono::high_resolution_clock::now();
				time_taken = chrono::duration<double>(end - start).count();
				cout << "Pthread H flip took: " << time_taken << " Seconds" << endl;
            }
            else if (std::string(argv[1]) == "-V")
            {
				start = chrono::high_resolution_clock::now();

                output = input.flipVertically();

				end = chrono::high_resolution_clock::now();
				time_taken = chrono::duration<double>(end - start).count();
				cout << "Pthread V flip took: " << time_taken << " Seconds" << endl;
            }
            else
            {
                throw "Invalid option";
            }

            // Save the output
            output.saveASCII(argv[3]);
        }

        else
        {
            std::string error_message;
            error_message += "Invalid command line\n";
            error_message += "Usage:\t";
            error_message += argv[0];
            error_message += "   -H or -V";
            error_message += "   input_ascii_file.txt";
            error_message += "   output_ascii_file.txt";
            error_message += "   [number_of_threads (default: 0)]";

            throw error_message;
        }

		
    }
    // An error occured
    catch (const std::exception& error)
    {
        error_code = 1;
        std::cerr << error.what() << std::endl;
    }
    catch (const std::string& error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (const char* error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (...)
    {
        error_code = 1;
        std::cerr << "Unknown error" << std::endl;
    }

    return (error_code);
}
