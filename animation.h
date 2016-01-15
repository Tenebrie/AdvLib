
#include "core.h"
#include "drawable.h"

#define LIMIT_ANIMATIONS		64

#define ANIM_IDLE				0
#define ANIM_MOVE				1

namespace adv
{
	class cAnimationData
	{
	public:
		vector<int> frameList;
	};

	class cAnimatedDrawable : public cDrawable
	{
	private:
		int __frame;
		int __animation;
		bool __animReady[LIMIT_ANIMATIONS];
		cAnimationData __animData[LIMIT_ANIMATIONS];
	public:
		int frame() { return __frame; }						// Get current frame
		int animation() { return __animation; }				// Get current animation
		
		void setFrame(int frame = -1);						// Set the animation frame. If 'frame' == -1, set the next frame
		void setAnimation(int anim, bool reset = true);		// Set the current animation

		/*
		// Create the frame list.
		*/
		void addFrame(int anim, int frame);
		void addFrame(int anim, string frame);
		void addAnimation(int anim, vector<int> frameList);
		void addAnimation(int anim, vector<string> frameList);
	};
}