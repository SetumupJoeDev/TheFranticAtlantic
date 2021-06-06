#ifndef SETTINGS_H
#define SETTINGS_H

#include "SFML/Graphics.hpp"

namespace Settings
{
	namespace Game
	{

		//The file containing the game's high scores
		const std::string g_highScoreFile = "HighScores/HighScores.txt";

		namespace Window
		{
			//The window's title
			const std::string g_gameName = "The Frantic Atlantic";		//For some reason using const char* gave me multiple declaration errors, changed to string to fix

			//The height of the game window when it launches
			const int g_windowHeight = 720;

			//The width of the game window when it launches
			const int g_windowWidth = 1280;

			//The filename of the window icon
			const std::string g_windowIconFile = "Textures/BasicEnemy.png";

		};

		namespace Menus
		{

			//The position of the background image
			const sf::Vector2f g_backgroundPosition( 640.0f, 360.0f );

			//The scale of the backgound image for the main menu
			const sf::Vector2f g_mainMenuImageScale( 2.0f, 2.0f );

			//The background image used for the main menu
			const std::string g_mainMenuImage = "Textures/MainMenuArt.png";

			//The background image used for the game
			const std::string g_gameBackgroundImage = "Textures/BackgroundArt.png";

			//The background image used for the death screen
			const std::string g_deathScreenImage = "Textures/DeathScreen.png";

		};

	};

	namespace EnemyBase
	{

		namespace Health
		{

			//The maximum health that the base enemy can have
			const int g_baseHealth = 1;

		}

		namespace Movement
		{

			//The amount by which the base enemy is moved down the screen when it reaches a boundary
			const int g_verticalMovementDistance = 15;

			//The speed at which the base enemy moves horizontally
			const int g_horizontalMoveSpeed = 25;

			//The amount by which the enemy's move speed is incremented when it moves down vertically
			const float g_speedIncrementValue = 5.0f;

		}

		namespace Sounds
		{

			//The sound that plays when enemies fire projectiles
			const std::string g_enemyFireSound = "Sounds/EnemyFire.wav";

		}

		namespace Textures
		{

			//The texture used to represent the base enemy
			const std::string g_enemyTexture = "Textures/BasicEnemy.png";

			//A variant texture for the enemy
			const std::string g_enemyVariantTexture = "Textures/EnemyVariant01.png";

			//The texture used to represent the enemies' projectiles
			const std::string g_enemyProjectileTexture = "Textures/EnemyProjectile.png";

		}

		namespace Weapons
		{

			//The speed of the projectiles fired by the base enemy
			const int g_enemyProjectileSpeed = 200;

		}

	}

	namespace EnemyManager
	{


		//The number of enemies in the array of enemies
		const int g_numberOfEnemies = 55;
		
		//The X position of the first positioned enemy
		const int g_initialEnemyXPos = 365;

		//The furthest point that an enemy can be spawned at on the X axis
		const int g_enemyXPosLimit = 890;

		//The Y position of the first positioned enemy
		const int g_initialEnemyYPos = 75;

		//The amount the player's score should increase by when they kill an enemy
		const int g_scoreValue = 10;

		//The distance between each enemy placement on both the X and Y
		const int g_enemySpacing = 50;

		//The distance the enemies can move to either side
		const float g_enemyMovementDistance = 200.0f;

		//The time between enemies firing projectiles
		const float g_firingInterval = 1.0f;

	}

	namespace GameText
	{

		//The default font for the text elements of the game
		const std::string g_defaultTextFont = "Fonts/AtlantisInlineGrunge.ttf";

		//The default colour of the text elements in the game
		const sf::Color g_defaultTextColour = sf::Color::Yellow;

		//The default text content for all text elements in the game
		const std::string g_defaultTextContent = "Default Text";

	};

	namespace MenuManager
	{

		//The total number of buttons in the array of buttons
		const int g_numberOfButtons = 10;

		//The speed at which the buttons move during transitions
		const float g_buttonTransitionSpeed = 25.0f;

		//The speed at with the title moves during transitions
		const float g_titleTransitionSpeed = 5.0f;

		namespace Buttons
		{

			//The texture used to represent the buttons in the menus
			const std::string g_buttonTexture = "Textures/ButtonBase.png";

			//The sound played when a button is clicked
			const std::string g_buttonClickSound = "Sounds/ButtonClick.wav";

			namespace Labels
			{

				//The label for the "Play" button
				const std::string g_playButtonLabel = "Play!";

				//The label for the "Options" button
				const std::string g_optionsButtonLabel = "Options";

				//The label for the "Quit" button
				const std::string g_quitButtonLabel = "Quit";

				//The label for the "Option One" button
				const std::string g_toggleFullScreenButtonLabel = "Toggle Fullscreen";

				//The label for the "Option Two" button
				const std::string g_muteMusicButtonLabel = "Toggle Music Mute";

				//The label for the "Back" button
				const std::string g_backButtonLabel = "Back";

				//The label for the "Return to Main" button
				const std::string g_mainMenuButtonLabel = "Main menu";

				//The character size of the text on the main menu buttons
				const int g_mainMenuButtonCharSize = 30;

				//The character size of the text on the options menu buttons
				const int g_optionsButtonCharSize = 15;

				//The character size of the text on the game over menu buttons
				const int g_gameOverButtonCharSize = 20;

			};

			namespace Vectors
			{

				//The position of the "Play" button when it is on screen
				const sf::Vector2f g_playButtonOnScreenPos( 640.0f, 360.0f );

				//The position of the "Play" button when it is off screen
				const sf::Vector2f g_playButtonOffScreenPos( 1480.0f, 360.0f );

				//The position of the "Options" button when it is on screen
				const sf::Vector2f g_optionsButtonOnScreenPos( 640.0f, 449.0f );

				//The position of the "Options" button when it is off screen
				const sf::Vector2f g_optionsButtonOffScreenPos( 1480.0f, 449.0f );

				//The position of the "Play" button when it is on screen
				const sf::Vector2f g_quitButtonOnScreenPos( 640.0f, 538.0f );

				//The position of the "Play" button when it is off screen
				const sf::Vector2f g_quitButtonOffScreenPos( 1480.0f, 538.0f );

			};

		};

		namespace Titles
		{

			//The text conent for the title on the main menu
			const std::string g_mainMenuTitle = "The Frantic Atlantic";

			//The text content for the title on the options menu
			const std::string g_optionsMenuTitle = "Options";

			//The text content for the title on the game over menu
			const std::string g_gameOverTitle = "Game Over!";

			//The character size for the menu title
			const int g_titleCharSize = 60;

			namespace Vectors
			{

				//The position of the menu's title when it is on screen
				const sf::Vector2f g_titleOnScreenPos( 640.0f, 120.0f );

				//The position of the menu's title when it is off screen
				const sf::Vector2f g_titleOffScreenPos( 640.0f, -200.0f );

				//The position of the text that displays the player's final score
				const sf::Vector2f g_finalScorePosition( 640.0f, 240.0f );

			};
		};
	};

	namespace MusicManager
	{

		//The music file for the main menu theme
		const std::string g_mainMenuMusic = "Sounds/Music/MainMenuTheme.wav";

		//The music file for the game's theme
		const std::string g_inGameMusic = "Sounds/Music/InGameTheme.wav";

		//The music file for the death screen theme
		const std::string g_deathScreenMusic = "Sounds/Music/GameOverTheme.wav";

	};

	namespace ParticleSystem
	{

		//The number of particles stored in the array of particles
		const int g_numParticles = 100;

	};

	namespace Player
	{

		namespace Movement
		{

			//The speed at which the player will move
			const float g_moveSpeed = 150.0f;

			//The speed at which the player rotates while moving
			const float g_rotationSpeed = 0.85f;

			//The rotation of the player while moving left
			const int g_leftRotation = 335;

			//The rotation of the player while moving right
			const int g_rightRotation = 25;

		};

		namespace Weapons
		{

			//The amount of time between the player firing and being able to fire again
			const float g_weaponCooldown = 0.85f;

			//The speed that the player's base projectiles move at
			const float g_torpedoSpeed = -200.0f;
		};

		namespace CountdownTimers
		{

			//The amount of time that the player is invulnerable for after respawning
			const float g_invulnerabilityDuration = 2.0f;

			//The amount of time it takes for the player to respawn after being killed
			const float g_respawnCooldownDuration = 1.75f;

		};

		namespace Boundaries
		{

			//The leftmost point that the ship is able to move to before being stopped
			const int g_leftBound = 80;

			//The rightmost point that the ship is able to move to before being stopped
			const int g_rightBound = 1200;

		};

		namespace Lives
		{

			//The number of lives that the player starts with
			const int g_initialLivesCount = 3;

		};

		namespace Sounds
		{

			//The sound that plays when the player fires their weapon
			const std::string g_playerWeaponFire = "Sounds/FireWeapon.wav";

			//The sound that plays when the player's ship is destroyed
			const std::string g_playerKilled = "Sounds/SubmarineDestroyed.wav";

		};

		namespace Textures
		{

			//The texture used to represent the player's ship
			const std::string g_playerShipTexture = "Textures/SubmarineSprite.png";

			//The texture used to represent the player's base torpedo projectiles
			const std::string g_playerTorpedoTexture = "Textures/TorpedoSprite.png";

			//The texture used to represent the bubble particles that come from the engine
			const std::string g_bubbleParticleTexture = "Textures/BubbleSprite.png";

		};

		namespace Vectors
		{

			//The position that the player's ship spawns at
			const sf::Vector2f g_playerSpawnPoint( Boundaries::g_leftBound + Boundaries::g_rightBound * 0.5f, 650 );

			//The scale that the player will be set to
			const sf::Vector2f g_playerScale( 1.5f, 1.5f );

		};

		namespace ParticleSystems
		{

			namespace EngineParticleSystem
			{

				//The lifetime of each particle emitted from the emitter
				const float g_engineParticleLifetime = 0.55f;

				//The interval between each particle being emitted from the emitter
				const float g_engineParticleEmissionInterval = 0.15f;

				//The speed at which particles emitted from this emitter move
				const float g_engineParticleMoveSpeed = 75.0f;

				//The maximum number of active particles this emitter can have
				const int g_engineParticleLimit = 75;

				//The number of particles this emitter emits in an emission
				const int g_engineParticleNumInEmission = 4;

				//The radius of the emission zone of this particle system
				const int g_engineParticleEmissionRadius = 5;

				//The scale of the particles this system should emit
				const sf::Vector2f g_engineParticleScale( 0.35f, 0.35f );

			};

			namespace TorpedoParticleSystem
			{

			};

		};

	};

	namespace Projectile
	{

		//The scale of the projectiles
		const sf::Vector2f g_projectileScale( 0.5f, 0.5f );

		//The highest point the projectile can reach before it is set as inactive
		const float g_projectileMaxYPos = 740.0f;

		//The lowest point the projectile can reach before it is set as inactive
		const float g_projectileMinYPos = -20.0f;

	};

	namespace ProjectileManager
	{

		//The number of projectiles stored in the array of projectiles
		const int g_numProjectiles = 20;

	};

	namespace Shield
	{
		//The maximum health that the shield can have
		const int g_maxHealth = 25;

		//The movement speed of the shield
		const float g_shieldMoveSpeed = 25.0f;
	}

	namespace UIManager
	{

		//The on-screen position of the lives counter
		const sf::Vector2f g_livesCounterPosition( 75.0f, 25.0f );

		//The on-screen position of the score counter
		const sf::Vector2f g_scoreCounterPosition( 1190.0f, 25.0f );

	};

};

#endif