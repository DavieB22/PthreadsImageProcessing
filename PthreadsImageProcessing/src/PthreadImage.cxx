/**
********************************************************************************
*
*   @file       PthreadImage.cxx
*
*   @brief      Class to handle a greyscale image using Pthread to speedup computations.
*
*   @version    1.0
*
*   @todo       Write here anything you did not implement.
*
*   @date       17/10/2019
*
*   @author     Franck Vidal
*   @author     YOUR NAME
*
*
********************************************************************************
*/


//******************************************************************************
//  Include
//******************************************************************************
#include <pthread.h> // Header file for stringstream
#include <vector>
#include <iostream>
#include "PthreadImage.h"


using namespace std;

struct ThreadData 
{
	pthread_t thread_id;
	unsigned int start_id;
	unsigned int end_id;
	const Image* input;
	Image* output;
};

//--------------------------------------------------------
PthreadImage::PthreadImage(unsigned int aNumberOfThreads):
//--------------------------------------------------------
        Image(),
        m_thread_number(aNumberOfThreads)
//--------------------------------------------------------
{}


//--------------------------------------------------------
PthreadImage::PthreadImage(const Image& anImage,
                           unsigned int aNumberOfThreads):
//--------------------------------------------------------
		Image(anImage),
        m_thread_number(aNumberOfThreads)
//--------------------------------------------------------
{}


//------------------------------------------------------
PthreadImage::PthreadImage(const PthreadImage& anImage):
//------------------------------------------------------
		Image(anImage),
        m_thread_number(anImage.m_thread_number)
//------------------------------------------------------
{}


//-------------------------------------------------------
PthreadImage::PthreadImage(const float* apData,
                           unsigned int aWidth,
                           unsigned int aHeight,
                           unsigned int aNumberOfThreads):
//-------------------------------------------------------
        Image(apData, aWidth, aHeight),
        m_thread_number(aNumberOfThreads)
//-------------------------------------------------------
{}


    //--------------------------------------------------------
PthreadImage::PthreadImage(unsigned int aWidth,
                           unsigned int aHeight,
                           float aDefaultValue,
                           unsigned int aNumberOfThreads):
//--------------------------------------------------------
        Image(aWidth, aHeight, aDefaultValue),
        m_thread_number(aNumberOfThreads)
//--------------------------------------------------------
{}


//---------------------------
PthreadImage::~PthreadImage()
//---------------------------
{}


//------------------------------------------------------------------
void PthreadImage::setNumberOfThreads(unsigned int aNumberOfThreads)
//------------------------------------------------------------------
{
    m_thread_number = aNumberOfThreads;
}


//---------------------------------------------------
unsigned int PthreadImage::getNumberOfThreads() const
//---------------------------------------------------
{
    return m_thread_number;
}


//---------------------------------------------------------
PthreadImage& PthreadImage::operator=(const Image& anImage)
//---------------------------------------------------------
{
    Image::operator=(anImage);
    return *this;
}


//----------------------------------------------------------------
PthreadImage& PthreadImage::operator=(const PthreadImage& anImage)
//----------------------------------------------------------------
{
    Image::operator=(anImage);
    m_thread_number = anImage.m_thread_number;
    return *this;
}


//-------------------------------------------------------
bool PthreadImage::operator==(const Image& anImage) const
//-------------------------------------------------------
{
    if (m_thread_number == 0 || m_thread_number == 1)
    {
        return Image::operator==(anImage);
    }
    else
    {
        if (m_width != anImage.getWidth())
        {
            return (false);
        }

        if (m_height != anImage.getHeight())
        {
            return (false);
        }

        // Add your code here




        return true;
    }
}


//------------------------------------------
PthreadImage PthreadImage::operator!() const
//------------------------------------------
{
    if (m_thread_number == 0 || m_thread_number == 1)
    {
        return PthreadImage(Image::operator!(), m_thread_number);
    }
    else
    {
        // Create an image of the right size
        PthreadImage temp(getWidth(), getHeight(), m_thread_number);

        // Add your code here




        return temp;
    }
}


//------------------------------------------------------------------
PthreadImage PthreadImage::shiftScaleFilter(float aShiftValue,
                                            float aScaleValue) const
//------------------------------------------------------------------
{
    if (m_thread_number == 0 || m_thread_number == 1)
    {
        return PthreadImage(Image::shiftScaleFilter(aShiftValue, aScaleValue), m_thread_number);
    }
    else
    {
        // Create an image of the right size
        PthreadImage temp(getWidth(), getHeight(), m_thread_number);

        // Add your code here




        return temp;
    }
}


//------------------------------------------
PthreadImage PthreadImage::logFilter() const
//------------------------------------------
{
    if (m_thread_number == 0 || m_thread_number == 1)
    {
        return PthreadImage(Image::logFilter(), m_thread_number);
    }
    else
    {
        // Create an image of the right size
        PthreadImage temp(getWidth(), getHeight(), m_thread_number);

        // Add your code here




        return temp;
    }
}

//Declare a callabck fucntion for Horizontal flip
void* H_flip_callback_function(void* aThreadData);


//-------------------------------------------------
PthreadImage PthreadImage::flipHorizontally() const
//-------------------------------------------------
{

    if (m_thread_number == 0 || m_thread_number == 1)
    {
        return PthreadImage(Image::flipHorizontally(), m_thread_number);
    }
	else
	{
		// Create an image of the right size
		PthreadImage temp(getWidth(), getHeight(), m_thread_number);

		//Workload allocation
		//Create a vector of type ThreadData whcih is constructed at the top of the class under Struct ThreadData. Pass in the number of threads.
		vector<ThreadData> p_thread_data(m_thread_number);

		//create an integer to hold the last element. inizialize it as -1.
		int last_element = -1;
		//create an unsigned int to hold how many cells we need per thread. For the image we want the width and height divided by the number of threads. 
		unsigned int cells_per_thread = getHeight() * getWidth() / m_thread_number;
		//Next create a variable to hold the remainder of the sum. 
		unsigned int remainder = getHeight() * getWidth() % m_thread_number;

		//print the number of cells per thread to the console
		cout << "Default number for cells per thread: " << cells_per_thread << endl;

		//inizialize the threads with a for loop to interate through each thread and populate it
		for (int i = 0; i < m_thread_number; i++)
		{
			//thread ids correspond with the for loop index values. 
			p_thread_data[i].thread_id = i;
			//start is last element + 1 i.e -1 + 1 start = 0.
			p_thread_data[i].start_id = ++last_element;
			p_thread_data[i].end_id = last_element + cells_per_thread - 1;
			p_thread_data[i].input = this;
			p_thread_data[i].output = &temp;

			//if the remainder is > thats 0 add 1 to the end them remove 1 remainder. 
			if (remainder > 0)
			{
				p_thread_data[i].end_id++;
				--remainder;
			}

			//make the last element not = -1 but = the end of the threads.
			last_element = p_thread_data[i].end_id;

			//print to console what number then thread start and end on 
			cout << "Thread[" << i << "] starts with " << p_thread_data[i].start_id << " and stops on " << p_thread_data[i].end_id << endl;

		}

		//create the threads with antoher for loop
		for (int i = 0; i < m_thread_number; i++)
		{
			pthread_create(&p_thread_data[i].thread_id, NULL, H_flip_callback_function, &p_thread_data[i]);
		}

		//Wait for each thread to complete;
		for (int i = 0; i < m_thread_number; i++)
		{
			pthread_join(p_thread_data[i].thread_id, NULL);
		}

		return temp;
	}
}


//Define the callabck fucntion for Horizontal flip
void* H_flip_callback_function(void* aThreadData)
{

	//convert void to Thread data
	ThreadData* p_thread_data = static_cast<ThreadData*>(aThreadData);

	for (int i = p_thread_data->start_id; i <= p_thread_data->end_id; i++)
	{
			// Process every row of the image
		for (unsigned int j = 0; j < m_height; ++j)
		{
			// Process every column of the image
			for (unsigned int i = 0; i < m_width / 2; ++i)
			{
				(*(p_thread_data->output))(              i, j) = getPixel(m_width - i - 1, j);
				(*(p_thread_data->output))(m_width - i - 1, j) = getPixel(              i, j);
			}
		}

	}

	return 0;
}


//-----------------------------------------------
PthreadImage PthreadImage::flipVertically() const
//-----------------------------------------------
{
    if (m_thread_number == 0 || m_thread_number == 1)
    {
        return PthreadImage(Image::flipVertically(), m_thread_number);
    }
    else
    {
		// Create an image of the right size
		PthreadImage temp(getWidth(), getHeight(), m_thread_number);

	
		return temp;

    }
}

