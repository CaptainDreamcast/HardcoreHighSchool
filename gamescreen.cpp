#include "gamescreen.h"

#include <prism/blitz.h>

#include "storyscreen.h"

class GameScreen
{
public:
    MugenSpriteFile mSprites;
    MugenAnimations mAnimations;
    MugenSounds mSounds;

            enum class StudentType
        {
            DELINQUENT,
            LAWYER,
            CLOWN,
            PRINCIPAL
        };


    class SelectScreen
    {
public:
        GameScreen* m;
        bool isActive = false;
        SelectScreen(GameScreen* t) : m(t) {}

        MugenAnimationHandlerElement* mBG;
        MugenAnimationHandlerElement* mDesk;
        MugenAnimationHandlerElement* mMenu;
        int mNameText;
        int mDescriptionText;
        int mTroubleLevelText;

        int mTotalTrouble = 0;
        int mTotalTroubleLevelText;

        struct SelectableStudent
        {
            StudentType mType;
            std::string name;
            std::string description;
            int mTroubleLevel;
        };

        bool areSelectableStudentsLoaded = false;
        std::vector<SelectableStudent> mActiveSelectableStudents;

        MugenAnimationHandlerElement* mSmallBG;
        std::vector<MugenAnimationHandlerElement*> mSmallChibisLeft;
        std::vector<MugenAnimationHandlerElement*> mSmallChibisRight;

        void loadSmallPreview()
        {
            mSmallBG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 101), &m->mSprites, Vector3D(0, 0, 40));
            mSmallChibisLeft.resize(10);
            mSmallChibisRight.resize(10);
            for(int i = 0; i < 10; i++)
            {
                mSmallChibisLeft[i] = addMugenAnimation(getMugenAnimation(&m->mAnimations, 110), &m->mSprites, Vector3D(150 - i * 20, 40, 41));
                mSmallChibisRight[i] = addMugenAnimation(getMugenAnimation(&m->mAnimations, 110), &m->mSprites, Vector3D(170 + i * 20, 40, 41));
                setMugenAnimationBaseDrawScale(mSmallChibisLeft[i], 0.5);
                setMugenAnimationBaseDrawScale(mSmallChibisRight[i], 0.5);
                setMugenAnimationFaceDirection(mSmallChibisRight[i], 0);
                setMugenAnimationVisibility(mSmallChibisLeft[i], false);
                setMugenAnimationVisibility(mSmallChibisRight[i], false);
            }
        }

        std::vector<std::vector<SelectableStudent>> mLevelSelectableStudents = {
            {
                {StudentType::DELINQUENT, 
                    "Harumichi Bouya", 
                    "Sometimes puts umbrellas over cardboard boxes with abandoned cats in them. He only has those little cocktail umbrellas, but the thought counts.", 
                    10},
                {StudentType::LAWYER, 
                    "Berry Richman", 
                    "Passed the bar exam, but very bad in geography, so he has repeated the same year for 25 years.", 
                    20},
                {StudentType::CLOWN, 
                    "Bobo", 
                    "Runs a biker gang with other clowns on their little trycicles.", 
                    30},
                {StudentType::DELINQUENT, 
                    "Taeson Maeda", 
                    "Head of the boxing club. But they're not sure what what boxing is so they just make little packages for the other students.", 
                    20},
                 {StudentType::LAWYER, 
                    "Miles Millington", 
                    "Runs an evil lawyer gang targetting small innocent emulator developers. Rumo- Well, facts say a large company is pulling the strings.", 
                    40},
                {StudentType::CLOWN, 
                    "BONZO", 
                    "Gets mad when someone makes fun of his nose. Or his feet. Or his outfit. Why are you even a clown, man?", 
                    20},
            },
            {
                {StudentType::DELINQUENT, 
                    "Harumichi Bouya", 
                    "Now he's making little umbrella hats for the cats, he must be stopped.", 
                    10},
                {StudentType::LAWYER, 
                    "Berry Richman", 
                    "Rumors say he has ruled over the 10th-graders for more than a decade as their Accounting King.", 
                    20},
                {StudentType::CLOWN, 
                    "Bobo", 
                    "Secretly feels he has been left with shoes that are too large to fill by the previous Clown boss.", 
                    30},
                {StudentType::DELINQUENT, 
                    "Taeson Maeda", 
                    "Has become more violent after he heard that the phrase 'sending someone packing' might be related to boxing.", 
                    20},
                 {StudentType::LAWYER, 
                    "Miles Millington", 
                    "James Bond stopped his scheme to melt the ice caps and add more oceanic accounting.", 
                    40},
                {StudentType::CLOWN, 
                    "Formerlyd BONZO", 
                    "Currently soul searching. As a clown. Why are you still a clown, man? For crying out loud.", 
                    20},
            },
            {
                {StudentType::DELINQUENT, 
                    "Harumichi Bouya", 
                    "Protected cats in the hail with his own body and died heroically. But why is he here then? Who is writing these descriptions?", 
                    10},
                {StudentType::LAWYER, 
                    "Berry Richman", 
                    "Don't ask about his cousin Pleynly Poorman.", 
                    20},
                {StudentType::CLOWN, 
                    "Bobo", 
                    "On the run from the cops, he's currently living with 20 other clowns out of his clown car.", 
                    30},
                {StudentType::DELINQUENT, 
                    "Taeson Maeda", 
                    "HE FOUND OUT WHAT BOXING IS, RED ALERT, I REPEAT RED ALE- ARGH!", 
                    20},
                 {StudentType::LAWYER, 
                    "Miles Millington", 
                    "Currently running for dark underground unelected world ruler. Won't let him pass that PE exam though.", 
                    40},
                {StudentType::CLOWN, 
                    "BONZO", 
                    "Has returned with burning vigour to get a pie thrown in his face. A true man's man now, and a true clown's clown.", 
                    20},
            }
        };

        MugenAnimationHandlerElement* mStudentAnimation;
        int mSelectedStudentIndex = 0;

        MugenAnimationHandlerElement* mLeftArrow;
        MugenAnimationHandlerElement* mRightArrow;

        Vector2D arrowBasePositionLeft = Vector2D(20, 112);
        Vector2D arrowBasePositionRight = Vector2D(150, 112);

        void load()
        {
            mBG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 1), &m->mSprites, Vector3D(0, 0, 1));
            mDesk = addMugenAnimation(getMugenAnimation(&m->mAnimations, 2), &m->mSprites, Vector3D(0, 0, 49));
            mStudentAnimation = addMugenAnimation(getMugenAnimation(&m->mAnimations, 10), &m->mSprites, Vector3D(0, 0, 30));

            mMenu = addMugenAnimation(getMugenAnimation(&m->mAnimations, 5), &m->mSprites, Vector3D(180, 50, 50));
            mNameText = addMugenTextMugenStyle("Name", Vector3D(187, 65, 52), Vector3DI(1, 0, 1));
            mDescriptionText = addMugenTextMugenStyle("Description", Vector3D(187, 80, 52), Vector3DI(1, 0, 1));
            setMugenTextTextBoxWidth(mDescriptionText, 110);
            mTroubleLevelText = addMugenTextMugenStyle("Trouble Level", Vector3D(187, 167, 52), Vector3DI(1, 0, 1));

            mTotalTroubleLevelText = addMugenTextMugenStyle("Total Trouble Level: 0%", Vector3D(88, 189, 52), Vector3DI(1, 3, 1));

            mLeftArrow = addMugenAnimation(getMugenAnimation(&m->mAnimations, 3), &m->mSprites, Vector3D(20, 112, 53));
            mRightArrow = addMugenAnimation(getMugenAnimation(&m->mAnimations, 4), &m->mSprites, Vector3D(150, 112, 53));

            loadSmallPreview();
        }

        void updateLoadingSelectableStudents()
        {
            if (!areSelectableStudentsLoaded)
            {
                mActiveSelectableStudents = mLevelSelectableStudents[m->mLevel];
                areSelectableStudentsLoaded = true;
            } 
        }

        void goToNextLevel()
        {
            areSelectableStudentsLoaded = false;
            mTotalTrouble = 0;
            updateTotalTroubleText();
        }

        void resetLevel()
        {
            areSelectableStudentsLoaded = false;
            mTotalTrouble = 0;
            updateTotalTroubleText();
        }

        void updateGoingToFightScreen()
        {
            if (areSelectableStudentsLoaded && mActiveSelectableStudents.empty())
            {
                setMugenAnimationVisibility(mStudentAnimation, false);
                m->goToFight();
            }
        }

        int getAnimationNumberFromStudentType(StudentType tType)
        {
            if (tType == StudentType::DELINQUENT) return 10;
            if (tType == StudentType::LAWYER) return 11;
            if (tType == StudentType::CLOWN) return 12;
            return 0;
        }

        void updateShowingCurrentStudent() {
            if (areSelectableStudentsLoaded && !mActiveSelectableStudents.empty())
            {
                mSelectedStudentIndex = min(max(0, mSelectedStudentIndex), int(mActiveSelectableStudents.size() - 1));
                SelectableStudent& student = mActiveSelectableStudents[mSelectedStudentIndex];
                changeMugenAnimation(mStudentAnimation, getMugenAnimation(&m->mAnimations, getAnimationNumberFromStudentType(student.mType)));
                setMugenAnimationVisibility(mStudentAnimation, true);
                changeMugenText(mNameText, (std::string("Name: ") + student.name).c_str());
                changeMugenText(mDescriptionText, (std::string("Desc: ") + student.description).c_str());
                changeMugenText(mTroubleLevelText, (std::string("Trouble Level: ") + std::to_string(student.mTroubleLevel)).c_str());
            }
        }

        int arrowTicks = 0;
        void updateArrows()
        {
            if (areSelectableStudentsLoaded)
            {
                setMugenAnimationVisibility(mLeftArrow, mActiveSelectableStudents.size() > 1);
                setMugenAnimationVisibility(mRightArrow, mActiveSelectableStudents.size() > 1);
            }
            arrowTicks++;
            setMugenAnimationPositionX(mLeftArrow, arrowBasePositionLeft.x + sin(arrowTicks * 0.1) * 5);
            setMugenAnimationPositionX(mRightArrow, arrowBasePositionRight.x - sin(arrowTicks * 0.1) * 5);
        }

        void update() 
        {
            updateLoadingSelectableStudents();
            updateGoingToFightScreen();
            updateArrows();
            updateSelection();
            updateExpelling();
            updateSummoning();
            updateShowingCurrentStudent();
        }

        bool canSummon = false;
        void updateSummoning()
        {
            if (areSelectableStudentsLoaded && hasPressedAFlank() && canSummon)
            {
                addCurrentCharacterToFightScreen(mActiveSelectableStudents[mSelectedStudentIndex]);
                mTotalTrouble += mActiveSelectableStudents[mSelectedStudentIndex].mTroubleLevel;
                updateTotalTroubleText();
                tryPlayMugenSound(&m->mSounds, 1, 3);
                if(mTotalTrouble <= 100)
                {
                    mActiveSelectableStudents.erase(mActiveSelectableStudents.begin() + mSelectedStudentIndex);
                }
                canSummon = false;
            }
            if (!hasPressedAFlank())
            {
                canSummon = true;
            }
        }

        void updateTotalTroubleText()
        {
            changeMugenText(mTotalTroubleLevelText, (std::string("Total Trouble Level: ") + std::to_string(mTotalTrouble) + "%").c_str());
            if(mTotalTrouble > 100)
            {
                m->setCardActive(GameScreen::CardType::TROUBLE, [this]() {m->resetLevelToSelect();});
            }
        }

        void addCurrentCharacterToFightScreen(SelectableStudent& tStudent)
        {
            m->mFightScreen->addCharacter(tStudent.mType);
            updateVisibleChibis();
        }

        bool canExpel = false;
        void updateExpelling()
        {
            if (areSelectableStudentsLoaded && hasPressedRFlank() && canExpel)
            {
                mActiveSelectableStudents.erase(mActiveSelectableStudents.begin() + mSelectedStudentIndex);
                playExplosionAnimationAtPosition();
                
                canExpel = false;
            }
            if(!hasPressedRFlank())
            {
                canExpel = true;
            }
        }

        void playExplosionAnimationAtPosition()
        {
            auto animation = addMugenAnimation(getMugenAnimation(&m->mAnimations, 8000), &m->mSprites, Vector3D(91, 138, 60));
            tryPlayMugenSound(&m->mSounds, 1, 1);
            setMugenAnimationNoLoop(animation);
            setMugenAnimationBaseDrawScale(animation, 5);
        }

        void updateSelection()
        {
            if (areSelectableStudentsLoaded && mActiveSelectableStudents.size() > 1)
            {
                if (hasPressedLeftFlank())
                {
                    tryPlayMugenSound(&m->mSounds, 1, 5);
                    mSelectedStudentIndex = (mSelectedStudentIndex + mActiveSelectableStudents.size() - 1) % mActiveSelectableStudents.size();
                }
                if (hasPressedRightFlank())
                {
                    tryPlayMugenSound(&m->mSounds, 1, 5);
                    mSelectedStudentIndex = (mSelectedStudentIndex + 1) % mActiveSelectableStudents.size();
                }
            }
        }

        void setActive(bool isActive)
        {
            this->isActive = isActive;
            setMugenAnimationVisibility(mBG, isActive);
            setMugenAnimationVisibility(mDesk, isActive);
            setMugenAnimationVisibility(mMenu, isActive);
            setMugenTextVisibility(mNameText, isActive);
            setMugenTextVisibility(mDescriptionText, isActive);
            setMugenTextVisibility(mTroubleLevelText, isActive);
            setMugenAnimationVisibility(mLeftArrow, isActive);
            setMugenAnimationVisibility(mRightArrow, isActive);
            setMugenAnimationVisibility(mStudentAnimation, isActive);
            setMugenTextVisibility(mTotalTroubleLevelText, isActive);

            setMugenAnimationVisibility(mSmallBG, isActive);
            for(int i = 0; i < 10; i++)
            {
                setMugenAnimationVisibility(mSmallChibisLeft[i], false);
                setMugenAnimationVisibility(mSmallChibisRight[i], false);
            }


            if(isActive)
            {
                streamMusicFile("game/SELECT.ogg");
                updateVisibleChibis();
                
            }
        }

        void updateVisibleChibis()
        {
                for(int i = 0; i < 10; i++)
                {
                    setMugenAnimationVisibility(mSmallChibisLeft[i], false);
                    setMugenAnimationVisibility(mSmallChibisRight[i], false);
                }

                auto fightEnemies = m->mFightScreen->mActiveEnemies;
                for(int i = 0; i < fightEnemies.size(); i++)
                {
                    setMugenAnimationVisibility(mSmallChibisRight[i], true);
                    changeMugenAnimation(mSmallChibisRight[i], getMugenAnimation(&m->mAnimations, m->mFightScreen->getFightAnimationNumberFromStudentType(fightEnemies[i])));
                }

                auto fightStudents = m->mFightScreen->mActiveStudents;
                for(int i = 0; i < fightStudents.size(); i++)
                {
                    setMugenAnimationVisibility(mSmallChibisLeft[i], true);
                    changeMugenAnimation(mSmallChibisLeft[i], getMugenAnimation(&m->mAnimations, m->mFightScreen->getFightAnimationNumberFromStudentType(fightStudents[i])));
                }
        }
    };

    class FightScreen
    {
public:
        GameScreen* m;
        bool isActive = false;
        FightScreen(GameScreen* t) : m(t) {}


        MugenAnimationHandlerElement* mBG;

        struct FightCharacter
        {
            MugenAnimationHandlerElement* mAnimation;
            MugenAnimationHandlerElement* mHealthBarBG;
            MugenAnimationHandlerElement* mHealthBarFG;
            int isSet = false;
            int health = 1000;
        };

        std::vector<FightCharacter> mFightCharactersLeft;
        std::vector<FightCharacter> mFightCharactersRight;

        void load()
        {
            mBG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 100), &m->mSprites, Vector3D(0, 0, 1));

            mFightCharactersLeft.resize(10);
            for(int i = 0; i < mFightCharactersLeft.size(); i++)
            {
                mFightCharactersLeft[i].mAnimation = addMugenAnimation(getMugenAnimation(&m->mAnimations, 110), &m->mSprites, Vector3D(100 - 40 * i, 195, 2));
                mFightCharactersLeft[i].mHealthBarBG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 120), &m->mSprites, Vector3D(100 - 40 * i - 22, 130 - i * 10, 5));
                mFightCharactersLeft[i].mHealthBarFG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 121), &m->mSprites, Vector3D(100 - 40 * i + 1 - 22, 130 - i * 10, 6));
                setMugenAnimationVisibility(mFightCharactersLeft[i].mAnimation, false);
                setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarBG, false);
                setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarFG, false);
            }
            setMugenAnimationPositionX(mFightCharactersLeft[0].mAnimation, 130);
            setMugenAnimationPositionX(mFightCharactersLeft[0].mHealthBarBG, getMugenAnimationPosition(mFightCharactersLeft[0].mHealthBarBG).x + 30);
            setMugenAnimationPositionX(mFightCharactersLeft[0].mHealthBarFG, getMugenAnimationPosition(mFightCharactersLeft[0].mHealthBarFG).x + 30);

            mFightCharactersRight.resize(10);
            for(int i = 0; i < mFightCharactersRight.size(); i++)
            {
                mFightCharactersRight[i].mAnimation = addMugenAnimation(getMugenAnimation(&m->mAnimations, 110), &m->mSprites, Vector3D(220 + 40 * i, 195, 2));
                mFightCharactersRight[i].mHealthBarBG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 120), &m->mSprites, Vector3D(220 + 40 * i - 22, 130 - i * 10, 5));
                mFightCharactersRight[i].mHealthBarFG = addMugenAnimation(getMugenAnimation(&m->mAnimations, 121), &m->mSprites, Vector3D(220 + 40 * i + 1 - 22, 130 - i * 10, 6));
                setMugenAnimationVisibility(mFightCharactersRight[i].mAnimation, false);
                setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarBG, false);
                setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarFG, false);
                setMugenAnimationFaceDirection(mFightCharactersRight[i].mAnimation, 0);
            }
            setMugenAnimationPositionX(mFightCharactersRight[0].mAnimation, 190);
            setMugenAnimationPositionX(mFightCharactersRight[0].mHealthBarBG, getMugenAnimationPosition(mFightCharactersRight[0].mHealthBarBG).x - 30);
            setMugenAnimationPositionX(mFightCharactersRight[0].mHealthBarFG, getMugenAnimationPosition(mFightCharactersRight[0].mHealthBarFG).x - 30);
        }

        std::vector<std::vector<StudentType>> mLevelEnemies = {
            {StudentType::DELINQUENT, StudentType::CLOWN },
            {StudentType::DELINQUENT, StudentType::LAWYER, StudentType::LAWYER },
            {StudentType::DELINQUENT, StudentType::LAWYER, StudentType::CLOWN, StudentType::PRINCIPAL}
        };

        std::vector<StudentType> mActiveStudents;
        std::vector<StudentType> mActiveEnemies;

        void startLevel()
        {
            mActiveEnemies = mLevelEnemies[m->mLevel];
            mActiveStudents.clear();
        }

        void update() 
        {
            updateFightHappening();
            updateShowingEnemies();
            updateShowingStudents();
            updateFightWinning();
            updateFightLosing();
            updateLifeBars();
        }

        void updateFightWinning()
        {
            if((!mFightCharactersRight[0].isSet || mFightCharactersRight[0].health <= 0))
            {
                m->setCardActive(GameScreen::CardType::VICTORY, [this]() {m->goToNextLevel();});
            }
        }

        void updateFightLosing()
        {
            if((!mFightCharactersLeft[0].isSet || mFightCharactersLeft[0].health <= 0))
            {
                if(getMugenAnimationAnimationNumber(mFightCharactersRight[0].mAnimation) == 113)
                {
                    m->setCardActive(GameScreen::CardType::PRINCIPAL, [this]() {
                        setCurrentStoryDefinitionFile("game/OUTRO.def", 1);
                        setNewScreen(getStoryScreen());
                    });
                }
                else
                {
                    m->setCardActive(GameScreen::CardType::DEFEAT, [this]() {m->resetLevelToSelect();});
                }
            }
        }

        int reduceFighterHealth(int tHealth, int tDefenderAnimation, int tAttackerAnimation)
        {
            int baseReduction = 0;
            if(tDefenderAnimation == 110)
            {
                if(tAttackerAnimation == 110) baseReduction = 100;
                else if(tAttackerAnimation == 111) baseReduction = 200;
                else if(tAttackerAnimation == 112) baseReduction = 100;
                else if (tAttackerAnimation == 113) baseReduction = 200;
            }
            else if(tDefenderAnimation == 111)
            {
                if(tAttackerAnimation == 110) baseReduction = 100;
                else if(tAttackerAnimation == 111) baseReduction = 100;
                else if(tAttackerAnimation == 112) baseReduction = 200;
                else if (tAttackerAnimation == 113) baseReduction = 200;
            }
            else if(tDefenderAnimation == 112)
            {
                if(tAttackerAnimation == 110) baseReduction = 200;
                else if(tAttackerAnimation == 111) baseReduction = 100;
                else if(tAttackerAnimation == 112) baseReduction = 100;
                else if (tAttackerAnimation == 113) baseReduction = 200;
            }
            else if (tDefenderAnimation == 113)
            {
                baseReduction = 0;
            }

            return min(tHealth, baseReduction);
        }

        int fightTicks = 0;
        void updateFightHappening()
        {
            fightTicks++;
             if(mFightCharactersRight[0].isSet && mFightCharactersLeft[0].isSet && fightTicks % 10 == 0)
            {
              mFightCharactersRight[0].health -=  reduceFighterHealth(mFightCharactersRight[0].health, getMugenAnimationAnimationNumber(mFightCharactersRight[0].mAnimation), getMugenAnimationAnimationNumber(mFightCharactersLeft[0].mAnimation));
              mFightCharactersLeft[0].health -=  reduceFighterHealth(mFightCharactersLeft[0].health, getMugenAnimationAnimationNumber(mFightCharactersLeft[0].mAnimation), getMugenAnimationAnimationNumber(mFightCharactersRight[0].mAnimation));
              updateLifeBars();
            }
        }

        void updateLifeBars()
        {
            setMugenAnimationDrawScale(mFightCharactersRight[0].mHealthBarFG, Vector2D(mFightCharactersRight[0].health / 1000.0, 1));
            setMugenAnimationDrawScale(mFightCharactersLeft[0].mHealthBarFG, Vector2D(mFightCharactersLeft[0].health / 1000.0, 1));
        }

        int getFightAnimationNumberFromStudentType(StudentType tType)
        {
            if (tType == StudentType::DELINQUENT) return 110;
            if (tType == StudentType::LAWYER) return 111;
            if (tType == StudentType::CLOWN) return 112;
            if (tType == StudentType::PRINCIPAL) return 113;
            return 113;
        }

        void updateShowingEnemies()
        {
            if(mFightCharactersRight[0].isSet && mFightCharactersRight[0].health <= 0)
            {
                for(int i = 1; i < mFightCharactersRight.size(); i++)
                {
                    mFightCharactersRight[i - 1].isSet = mFightCharactersRight[i].isSet;
                    mFightCharactersRight[i - 1].health = mFightCharactersRight[i].health;
                    setMugenAnimationVisibility(mFightCharactersRight[i - 1].mAnimation, mFightCharactersRight[i].isSet);
                    setMugenAnimationVisibility(mFightCharactersRight[i - 1].mHealthBarBG, mFightCharactersRight[i].isSet);
                    setMugenAnimationVisibility(mFightCharactersRight[i - 1].mHealthBarFG, mFightCharactersRight[i].isSet);
                    changeMugenAnimation(mFightCharactersRight[i - 1].mAnimation, getMugenAnimation(&m->mAnimations, getMugenAnimationAnimationNumber(mFightCharactersRight[i].mAnimation)));
                }
                tryPlayMugenSound(&m->mSounds, 10, randfromInteger(0, 2));
            }
        }

        void updateShowingStudents()
        {
            if(mFightCharactersLeft[0].isSet && mFightCharactersLeft[0].health <= 0)
            {
                for(int i = 1; i < mFightCharactersLeft.size(); i++)
                {
                    mFightCharactersLeft[i - 1].isSet = mFightCharactersLeft[i].isSet;
                    mFightCharactersLeft[i - 1].health = mFightCharactersLeft[i].health;
                    setMugenAnimationVisibility(mFightCharactersLeft[i - 1].mAnimation, mFightCharactersLeft[i].isSet);
                    setMugenAnimationVisibility(mFightCharactersLeft[i - 1].mHealthBarBG, mFightCharactersLeft[i].isSet);
                    setMugenAnimationVisibility(mFightCharactersLeft[i - 1].mHealthBarFG, mFightCharactersLeft[i].isSet);
                    changeMugenAnimation(mFightCharactersLeft[i - 1].mAnimation, getMugenAnimation(&m->mAnimations, getMugenAnimationAnimationNumber(mFightCharactersLeft[i].mAnimation)));
                
                }
                tryPlayMugenSound(&m->mSounds, 10, randfromInteger(0, 2));
            }
        }

        void loadStudentsAtStartOfFight(){
            for(int i = 0; i < mFightCharactersLeft.size(); i++)
            {
                mFightCharactersLeft[i].isSet = false;
                mFightCharactersLeft[i].health = 1000;
                setMugenAnimationVisibility(mFightCharactersLeft[i].mAnimation, false);
                setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarBG, false);
                setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarFG, false);
            }

            for(int i = 0; i < mActiveStudents.size(); i++)
            {
                mFightCharactersLeft[i].isSet = true;
                mFightCharactersLeft[i].health = 1000;
                setMugenAnimationVisibility(mFightCharactersLeft[i].mAnimation, true);
                setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarBG, true);
                setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarFG, true);
                changeMugenAnimation(mFightCharactersLeft[i].mAnimation, getMugenAnimation(&m->mAnimations, getFightAnimationNumberFromStudentType(mActiveStudents[i])));
            }
        }

        void loadEnemiesAtStartOfFight()
        {
            for(int i = 0; i < mFightCharactersRight.size(); i++)
            {
                mFightCharactersRight[i].isSet = false;
                mFightCharactersRight[i].health = 1000;
                setMugenAnimationVisibility(mFightCharactersRight[i].mAnimation, false);
                setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarBG, false);
                setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarFG, false);
            }

            for(int i = 0; i < mActiveEnemies.size(); i++)
            {
                mFightCharactersRight[i].isSet = true;
                mFightCharactersRight[i].health = 1000;
                setMugenAnimationVisibility(mFightCharactersRight[i].mAnimation, true);
                setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarBG, true);
                setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarFG, true);
                changeMugenAnimation(mFightCharactersRight[i].mAnimation, getMugenAnimation(&m->mAnimations, getFightAnimationNumberFromStudentType(mActiveEnemies[i])));
            }
        }





        void addCharacter(StudentType tType)
        {
            mActiveStudents.push_back(tType);
        }

        void setActive(bool isActive)
        {
            setMugenAnimationVisibility(mBG, isActive);

            this->isActive = isActive;

            if(isActive)
            {
                loadStudentsAtStartOfFight();
                loadEnemiesAtStartOfFight();
            }
            else
            {
                for(int i = 0; i < mFightCharactersLeft.size(); i++)
                {
                    setMugenAnimationVisibility(mFightCharactersLeft[i].mAnimation, isActive);
                    setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarBG, isActive);
                    setMugenAnimationVisibility(mFightCharactersLeft[i].mHealthBarFG, isActive);
                }
                for(int i = 0; i < mFightCharactersRight.size(); i++)
                {
                    setMugenAnimationVisibility(mFightCharactersRight[i].mAnimation, isActive);
                    setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarBG, isActive);
                    setMugenAnimationVisibility(mFightCharactersRight[i].mHealthBarFG, isActive);
                }
            }

            if(isActive)
            {
                streamMusicFile("game/FIGHT.ogg");
            }
        }
    };

    enum class ActiveSubScreen
    {
        SELECT,
        FIGHT
    };

    std::shared_ptr<SelectScreen> mSelectScreen;
    std::shared_ptr<FightScreen> mFightScreen;
    ActiveSubScreen mActiveScreen;

    int mLevel = 0;

    GameScreen() {
        mSprites = loadMugenSpriteFileWithoutPalette("game/GAME.sff");
        mAnimations = loadMugenAnimationFile("game/GAME.air");
        mSounds = loadMugenSoundFile("game/GAME.snd");

        mSelectScreen = std::make_shared<SelectScreen>(this);
        mFightScreen = std::make_shared<FightScreen>(this);

        mCardAnimation = addMugenAnimation(getMugenAnimation(&mAnimations, -1), &mSprites, Vector3D(0, 0, 100));

        mSelectScreen->load();
        mFightScreen->load();

        resetLevelToSelect();
    }

    enum class CardType
    {
        TROUBLE,
        DAY1,
        DAY2,
        DAY3,
        PRINCIPAL,
        VICTORY,
        DEFEAT,
    };
    bool isCardActive = false;

    MugenAnimationHandlerElement* mCardAnimation;
    std::function<void()> mCardFinishedCB;

    void setCardActive(CardType type, std::function<void()> tCB)
    {
        isCardActive = true;
        mCardFinishedCB = tCB;
        changeMugenAnimation(mCardAnimation, getMugenAnimation(&mAnimations, cardTypeToAnimationNo(type)));
    }

    int cardTypeToAnimationNo(CardType type)
    {
        if(type == CardType::TROUBLE) return 1000;
        if(type == CardType::DAY1) return 1001;
        if(type == CardType::DAY2) return 1002;
        if(type == CardType::DAY3) return 1003;
        if(type == CardType::PRINCIPAL) return 1004;
        if(type == CardType::VICTORY) return 1005;
        if(type == CardType::DEFEAT) return 1006;
        return 1000;
    }

    void update() {
        if(isCardActive)
        {
            updateCard();
            return;
        }
        if(mActiveScreen == ActiveSubScreen::SELECT)
        {
            mSelectScreen->update();
        }
        else if(mActiveScreen == ActiveSubScreen::FIGHT)
        {
            mFightScreen->update();
        }
    }

    void updateCard()
    {
        if(hasPressedAFlank())
        {
            changeMugenAnimation(mCardAnimation, getMugenAnimation(&mAnimations, -1));
            tryPlayMugenSound(&mSounds, 1, 2);
            isCardActive = false;
            mCardFinishedCB();
        }
    }

    void goToFight()
    {
        mSelectScreen->setActive(false);
        mFightScreen->setActive(true);
        mActiveScreen = ActiveSubScreen::FIGHT;
    }

    void resetLevelBase()
    {
        if(mLevel == 0)
        {
            setCardActive(CardType::DAY1, [&]() { });
        }
        else if(mLevel == 1)
        {
            setCardActive(CardType::DAY2, [&]() { });
        }
        else if(mLevel == 2)
        {
            setCardActive(CardType::DAY3, [&]() { });
        }
        mFightScreen->startLevel();
        mFightScreen->setActive(false);
        mSelectScreen->setActive(true);
        mActiveScreen = ActiveSubScreen::SELECT;

    }

    void goToNextLevel()
    {
        mLevel++;
        mSelectScreen->goToNextLevel();
        resetLevelBase();
    }

    void resetLevelToSelect()
    {
        mSelectScreen->resetLevel();
        resetLevelBase();
    }
};

EXPORT_SCREEN_CLASS(GameScreen);