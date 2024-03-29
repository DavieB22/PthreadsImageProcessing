#ifndef __ImagePthread_h
#define __ImagePthread_h


/**
********************************************************************************
*
*   @file       PthreadImage.h
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
#include "Image.h"


//==============================================================================
/**
*   @class  PthreadImage
*   @brief  PthreadImage is a class to manage a greyscale image using Pthread
*           to speedup computations
*/
//==============================================================================
class PthreadImage: public Image
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
    //--------------------------------------------------------------------------
    /// Default constructor.
    /**
    * @param anImage: the image to copy
    */
    //--------------------------------------------------------------------------
    PthreadImage(unsigned int aNumberOfThreads = 4);


    //------------------------------------------------------------------------
    /// Copy constructor.
    /**
    * @param anImage: the image to copy
    * @param aNumberOfThreads: the number of threads (default: 4)
    */
    //------------------------------------------------------------------------
    PthreadImage(const Image& anImage, unsigned int aNumberOfThreads = 4);


    //------------------------------------------------------------------------
    /// Copy constructor.
    /**
    * @param anImage: the image to copy
    */
    //------------------------------------------------------------------------
    PthreadImage(const PthreadImage& anImage);


    //------------------------------------------------------------------------
    /// Constructor from an array.
    /**
    * @param apData: the array to copy
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    * @param aNumberOfThreads: the number of threads (default: 4)
    */
    //------------------------------------------------------------------------
    PthreadImage(const float* apData,
                 unsigned int aWidth,
                 unsigned int aHeight,
                 unsigned int aNumberOfThreads = 4);


    //------------------------------------------------------------------------
    /// Constructor to build a black image.
    /**
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    * @param aNumberOfThreads: the number of threads (default: 4)
    */
    //------------------------------------------------------------------------
    PthreadImage(unsigned int aWidth,
                 unsigned int aHeight,
                float aDefaultValue = 0.0,
                unsigned int aNumberOfThreads = 4);


    //------------------------------------------------------------------------
    /// Destructor.
    //------------------------------------------------------------------------
    ~PthreadImage();


    //------------------------------------------------------------------------
    /// Set the number of threads.
    /**
    * @param aNumberOfThreads: the number of threads
    */
    //------------------------------------------------------------------------
    void setNumberOfThreads(unsigned int aNumberOfThreads);


    //------------------------------------------------------------------------
    /// Get the number of threads.
    /**
    * @return the number of threads
    */
    //------------------------------------------------------------------------
    unsigned int getNumberOfThreads() const;


    //------------------------------------------------------------------------
    /// Assignment operator (also called copy operator).
    /**
    * @param anImage: the image to copy
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    PthreadImage& operator=(const Image& anImage);


    //------------------------------------------------------------------------
    /// Assignment operator (also called copy operator).
    /**
    * @param anImage: the image to copy
    * @return the updated version of the current image
    */
    //------------------------------------------------------------------------
    PthreadImage& operator=(const PthreadImage& anImage);


    //------------------------------------------------------------------------
    /// Operator Equal to
    /**
    * @param anImage: the image to compare with
    * @return true if the images are similar,
    *         false if they are different
    */
    //------------------------------------------------------------------------
    bool operator==(const Image& anImage) const;


	//------------------------------------------------------------------------
	/// Negation operator. Compute the negative of the current image.
	/**
	* @return the negative image
	*/
	//------------------------------------------------------------------------
	PthreadImage operator!() const;


	//------------------------------------------------------------------------
	/// Add aShiftValue to every pixel, then multiply every pixel
	/// by aScaleValue
	/**
	* @param aShiftValue: the shift parameter of the filter
	* @param aScaleValue: the scale parameter of the filter
    * @return the new image
	*/
	//------------------------------------------------------------------------
	PthreadImage shiftScaleFilter(float aShiftValue, float aScaleValue) const;


    //------------------------------------------------------------------------
	/// Apply a log filter on the image
    /**
    * @return the new image
	*/
	//------------------------------------------------------------------------
	PthreadImage logFilter() const;


    //------------------------------------------------------------------------
	/// Flip the image horizonatally
    /**
    * @return the new image
	*/
	//------------------------------------------------------------------------
	PthreadImage flipHorizontally() const;


    //------------------------------------------------------------------------
	/// Flip the image vertically
    /**
    * @return the new image
	*/
	//------------------------------------------------------------------------
	PthreadImage flipVertically() const;


//******************************************************************************
private:
    /// Number of threads
    unsigned int m_thread_number;
};

#endif
