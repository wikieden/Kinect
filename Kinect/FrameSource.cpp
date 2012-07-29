/***********************************************************************
FrameSource - Base class for objects that create streams of depth and
color frames.
Copyright (c) 2011-2012 Oliver Kreylos

This file is part of the Kinect 3D Video Capture Project (Kinect).

The Kinect 3D Video Capture Project is free software; you can
redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

The Kinect 3D Video Capture Project is distributed in the hope that it
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with the Kinect 3D Video Capture Project; if not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA
***********************************************************************/

#include <Kinect/FrameBuffer.h>
#include <Kinect/FrameSource.h>

namespace Kinect {

/****************************
Methods of class FrameSource:
****************************/

FrameSource::FrameSource(void)
	{
	}

FrameSource::~FrameSource(void)
	{
	}

bool FrameSource::hasDepthCorrectionCoefficients(void) const
	{
	return false;
	}

FrameBuffer FrameSource::getDepthCorrectionCoefficients(void) const
	{
	/* Get the source's frame size and create a result frame buffer: */
	const unsigned int* frameSize=getActualFrameSize(DEPTH);
	FrameBuffer result(frameSize[0],frameSize[1],frameSize[1]*frameSize[0]*sizeof(PixelDepthCorrection));
	
	/* Initialize the frame buffer to the identity transformation: */
	PixelDepthCorrection* pdcPtr=static_cast<PixelDepthCorrection*>(result.getBuffer());
	for(unsigned int y=0;y<frameSize[1];++y)
		for(unsigned int x=0;x<frameSize[0];++x,++pdcPtr)
			{
			pdcPtr->scale=1.0f;
			pdcPtr->offset=0.0f;
			}
	
	/* Return the identity correction map: */
	return result;
	}

}