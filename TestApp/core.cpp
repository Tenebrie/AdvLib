
#include "stdafx.h"
#include "game.h"
#include "window.h"

//====================================================================================
// Header
//====================================================================================


//====================================================================================
// Source code
//====================================================================================
cScene testScene;
adv::cDatabase<cUnit> unitDB;

void threadWindow(int id, adv::cArgs args)
{
	sf::RenderWindow winHandle(sf::VideoMode(800, 600), "Window", 7U);
	sf::RenderTexture texHandle;
	texHandle.create(800, 600);

	while (advCore.isThreadGood(id)) {
		sf::Event eventPoll;
		while (winHandle.pollEvent(eventPoll)) {
			advEvent.handle(eventPoll, &winHandle);
		}

		texHandle.clear(color(100, 100, 100));
		testScene.paint(&texHandle);
		advUI.paint(&texHandle);
		texHandle.display();

		sf::Sprite spr;
		spr.setTexture(texHandle.getTexture());
		winHandle.draw(spr);
		winHandle.display();
	}
	advCore.stopThread(id);
}

void timerMovement(adv::cEventArgs args)
{
	//float timemod = args.timer_tickDelay * (float)args.timer_tickTime;
	float timemod = 0.01f;

	float speedX = 100.00f * timemod;
	float accY = 10.f * timemod;
	cUnit* hero = &testScene.unitList[0];
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		hero->move(vec2f(-speedX, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		hero->move(vec2f(speedX, 0.f));
	}

	if (hero->pos().y < 590 - hero->size().y + hero->center().y || hero->vertAccel < 0.00f) {
		hero->move(vec2f(0.f, hero->vertAccel));
		hero->vertAccel += accY;
	}
	else {
		hero->vertAccel = 0.00f;
	}
}

int main()
{
	advCore.init();

	cHero hero;

	advUI.addFont("fontConsole", "C:/Windows/Fonts/consola.ttf", 16);
	//adv::cUIWindow* wnd = advUI.addWindow("wndMain");
	//wnd->addLabel("label0", vec2f(0, 0), L"Test String", "fontConsole", color(255, 255, 255));

	// Pushing object to the database
	cUnit db;
	db.resize(vec2f(32, 32));
	db.centralize(vec2f(16, 16));
	db.addFrame(adv::ANIM::IDLE, "asteroid.png");
	db.setAnimation(adv::ANIM::IDLE);
	unitDB.addObject("hero", db);

	db = cUnit();
	db.resize(vec2f(128, 80));
	db.centralize(vec2f(64, 75));
	db.addFrame(adv::ANIM::IDLE, "grass.png");
	db.setAnimation(adv::ANIM::IDLE);
	unitDB.addObject("land", db);

	// Creating test scene
	db = unitDB.getCopy("hero");
	db.moveto(vec2f(0, 0));
	testScene.unitList.push_back(db);
	db = unitDB.getCopy("land");
	db.moveto(vec2f(64, 605));
	testScene.unitList.push_back(db);
	db = unitDB.getCopy("land");
	db.moveto(vec2f(128, 605));
	testScene.unitList.push_back(db);
	db = unitDB.getCopy("land");
	db.moveto(vec2f(192, 605));
	testScene.unitList.push_back(db);
	db = unitDB.getCopy("land");
	db.moveto(vec2f(256, 605));
	testScene.unitList.push_back(db);

	// Creating logic timers
	advEvent.listenForTimer(TIMER_10MS, timerMovement);
	advEvent.listen(EVENT_KEY_PRESS, bind(&cHero::jump, &hero, _1), sf::Keyboard::W);
	
	advCore.addThread(threadWindow, 0);

	advCore.mainLoop();
	advCore.shut();

	return 0;
}

