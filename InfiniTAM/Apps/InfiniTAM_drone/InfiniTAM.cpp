// Copyright 2014-2017 Oxford University Innovation Limited and the authors of InfiniTAM

#include <cstdlib>
#include <iostream>
#include <thread>

#include "DroneEngine.h"
#include "UIEngine.h"

#include "../../InputSource/OpenNIEngine.h"
#include "../../InputSource/Kinect2Engine.h"
#include "../../InputSource/LibUVCEngine.h"
#include "../../InputSource/PicoFlexxEngine.h"
#include "../../InputSource/RealSenseEngine.h"
#include "../../InputSource/LibUVCEngine.h"
#include "../../InputSource/RealSense2Engine.h"
#include "../../InputSource/FFMPEGReader.h"
#include "../../ITMLib/ITMLibDefines.h"
#include "../../ITMLib/Core/ITMBasicEngine.h"
#include "../../ITMLib/Core/ITMBasicSurfelEngine.h"
#include "../../ITMLib/Core/ITMMultiEngine.h"

using namespace InfiniTAM::Engine;
using namespace InputSource;
using namespace ITMLib;

/** Create a default source of depth images from a list of command line
    arguments. Typically, @para arg1 would identify the calibration file to
    use, @para arg2 the colour images, @para arg3 the depth images and
    @para arg4 the IMU images. If images are omitted, some live sources will
    be tried.
*/
static void CreateDefaultImageSource(ImageSourceEngine* & imageSource, IMUSourceEngine* & imuSource, const char *arg1, const char *arg2, const char *arg3, const char *arg4)
{
	const char *calibFile = arg1;
	const char *filename1 = arg2;
	const char *filename2 = arg3;
	const char *filename_imu = arg4;

	if (strcmp(calibFile, "viewer") == 0)
	{
		imageSource = new BlankImageGenerator("", Vector2i(640, 480));
		printf("starting in viewer mode: make sure to press n first to initiliase the views ... \n");
		return;
	}

	while (imageSource == NULL)
	{
		if (imageSource == NULL)
		{
			printf("trying PMD PicoFlexx device\n");
			imageSource = new PicoFlexxEngine(calibFile);
			if (imageSource->getDepthImageSize().x == 0)
			{
				delete imageSource;
				imageSource = NULL;
			}
		}
	}

}

int main(int argc, char** argv)
try
{
	const char *arg1 = "";
	const char *arg2 = NULL;
	const char *arg3 = NULL;
	const char *arg4 = NULL;

	int arg = 1;
	do {
		if (argv[arg] != NULL) arg1 = argv[arg]; else break;
		++arg;
		if (argv[arg] != NULL) arg2 = argv[arg]; else break;
		++arg;
		if (argv[arg] != NULL) arg3 = argv[arg]; else break;
		++arg;
		if (argv[arg] != NULL) arg4 = argv[arg]; else break;
	} while (false);

	if (arg == 1) {
		printf("usage: %s [<calibfile> [<imagesource>] ]\n"
		       "  <calibfile>   : path to a file containing intrinsic calibration parameters\n"
		       "  <imagesource> : either one argument to specify OpenNI device ID\n"
		       "                  or two arguments specifying rgb and depth file masks\n"
		       "\n"
		       "examples:\n"
		       "  %s ./Files/Teddy/calib.txt ./Files/Teddy/Frames/%%04i.ppm ./Files/Teddy/Frames/%%04i.pgm\n"
		       "  %s ./Files/Teddy/calib.txt\n\n", argv[0], argv[0], argv[0]);
	}

	printf("initialising ...\n");
	ImageSourceEngine *imageSource = NULL;
	IMUSourceEngine *imuSource = NULL;

	CreateDefaultImageSource(imageSource, imuSource, arg1, arg2, arg3, arg4);
	if (imageSource==NULL)
	{
		std::cout << "failed to open any image stream" << std::endl;
		return -1;
	}

	ITMLibSettings *internalSettings = new ITMLibSettings();

	ITMMainEngine *mainEngine = NULL;
	switch (internalSettings->libMode)
	{
	case ITMLibSettings::LIBMODE_BASIC:
		mainEngine = new ITMBasicEngine<ITMVoxel, ITMVoxelIndex>(internalSettings, imageSource->getCalib(), imageSource->getRGBImageSize(), imageSource->getDepthImageSize());
		break;
	case ITMLibSettings::LIBMODE_BASIC_SURFELS:
		mainEngine = new ITMBasicSurfelEngine<ITMSurfelT>(internalSettings, imageSource->getCalib(), imageSource->getRGBImageSize(), imageSource->getDepthImageSize());
		break;
	case ITMLibSettings::LIBMODE_LOOPCLOSURE:
		mainEngine = new ITMMultiEngine<ITMVoxel, ITMVoxelIndex>(internalSettings, imageSource->getCalib(), imageSource->getRGBImageSize(), imageSource->getDepthImageSize());
		break;
	default: 
		throw std::runtime_error("Unsupported library mode!");
		break;
	}

	DroneEngine::Instance()->Initialise(mainEngine);


	UIEngine::Instance()->Initialise(argc, argv, imageSource, imuSource, mainEngine, "./Files/Out", internalSettings->deviceType);
	std::thread drone_thread(&DroneEngine::Run, DroneEngine::Instance());
	UIEngine::Instance()->Run();
	DroneEngine::Instance()->Stop();
	UIEngine::Instance()->Shutdown();

	drone_thread.join();
	DroneEngine::Instance()->Shutdown();


	delete mainEngine;
	delete internalSettings;
	delete imageSource;
	if (imuSource != NULL) delete imuSource;
	return 0;
}
catch(std::exception& e)
{
	std::cerr << e.what() << '\n';
	return EXIT_FAILURE;
}

