/**
 * @file ImageBase.hpp
 * @brief Base class containing some basic functionalities for images.
 * @author Mickael Pinto (mickael.pinto@live.fr)
 * @date October 2012
 * @details 
 */
#pragma once
#include <cstdio>
#include <cstdlib>
#include "image_pgm.hpp"
#include "image_ppm.hpp"

/**
 * \class ImageBase
 * \brief This class is a base class for images. It provides some basic functionalities for images.
 * \author Mickael Pinto
 * \date October 2012
 */
class ImageBase
{
	///////////// Enumerations
public:
	/**
	 * \brief Enumeration for the color planes of an image.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	typedef enum
	{
		PLAN_R,
		PLAN_G,
		PLAN_B
	} PLAN;

	///////////// Attributes
protected:
	unsigned char *data; /**< Pointer to the image data in unsigned char format */
	double *dataD;		 /**< Pointer to the image data in double format */

	bool color;	  /**< Flag indicating if the image is in color or not */
	int height;	  /**< Height of the image */
	int width;	  /**< Width of the image */
	int nTaille;  /**< Total size of the image data */
	bool isValid; /**< Flag indicating if the image is valid or not */

	image_pgm img_pgm; /**< Object for handling PGM images */
	image_ppm img_ppm; /**< Object for handling PPM images */
					   ///////////// Constructors/Destructors
protected:
	/**
	 * \brief Initializes the image object.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	void init();
	/**
	 * \brief Resets the image object.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	void reset();

public:
	/**
	 * \brief Default constructor for the ImageBase class.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	ImageBase(void);

	/**
	 * \brief Copy constructor for the ImageBase class.
	 * \param other The ImageBase object to copy.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	ImageBase(const ImageBase &other);

	/**
	 * \brief Constructor for the ImageBase class with specified width, height, and color mode.
	 * \param imWidth The width of the image.
	 * \param imHeight The height of the image.
	 * \param isColor Flag indicating if the image is in color or not.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	ImageBase(int imWidth, int imHeight, bool isColor);

	/**
	 * \brief Destructor for the ImageBase class.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	~ImageBase(void);

	///////////// Methods
protected:
	/**
	 * \brief Copies the data from another ImageBase object.
	 * \param copy The ImageBase object to copy.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	void copy(const ImageBase &copy);

public:
	/**
	 * \brief Gets the height of the image.
	 * \return The height of the image.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	int getHeight() { return height; };
	/**
	 * \brief Gets the width of the image.
	 * \return The width of the image.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	int getWidth() { return width; };

	/**
	 * \brief Gets the total size of the image data.
	 * \return The total size of the image data.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	int getTotalSize() { return nTaille; };
	/**
	 * \brief Gets the validity flag of the image.
	 * \return The validity flag of the image.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	int getValidity() { return isValid; };
	/**
	 * \brief Gets the color flag of the image.
	 * \return The color flag of the image.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	bool getColor() { return color; };
	/**
	 * \brief Gets the pointer to the image data in unsigned char format.
	 * \return The pointer to the image data in unsigned char format.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	unsigned char *getData() { return data; };
	/**
	 * \brief Loads an image from a file.
	 * \param filename The name of the file to load.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	void load(char *filename);

	/**
	 * \brief Saves the image to a file.
	 * \param filename The name of the file to save.
	 * \return True if the image was saved successfully, false otherwise.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	bool save(char *filename);
	/**
	 * \brief Gets a specific color plane of the image.
	 * \param plan The color plane to get.
	 * \return A new ImageBase object containing the specified color plane.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	ImageBase *getPlan(PLAN plan);
	/**
	 * \brief Overloaded operator[] to access the image data.
	 * \param l The index of the data to access.
	 * \return A pointer to the image data at the specified index.
	 * \author Mickael Pinto
	 * \date October 2012
	 */
	unsigned char *operator[](int l);
};
