#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "Component.hpp"
#include "Player.hpp"

namespace SYS
{
	class Events
	{
	public:
		// Handle Users Events
		static void handle(sf::RenderWindow&);
	};

	class Camera
	{
	public:
		// The Camera Follows The Player
		static void update(const Player&, sf::RenderWindow&, sf::Vector2f);
	};

	class Animation
	{
	public:
		// Updates The Animation Stages
		static void update(AnimatedSprite2D&,const Player::State&, float dt);
	private:
		static inline int counter = { 15 };
		static inline Player::State previousState = Player::State::IdleRight;
	};

	class Input
	{
	public:
		//	Get The Input to The Player
		static void update(COMP::Input&) noexcept;
		static void reset(COMP::Input&) noexcept;
	private:
		static inline bool dashReleased = { true };
	};

	class Gravity
	{
	public:
		// Update The Vertical Velocity According To The Gravity Value
		static void update(COMP::Transform&, float) noexcept;
	private:
		static constexpr float GRAVITY = 2500.f;
	};

	class Movement
	{
	public:
		//  Update Dash Timers And Dash Input
		static void updateDash(COMP::Input& input, Timer& dashTimer, Timer& dashCoolDown, float dt);

		//	Pick The Velocity According to The Player's Inputs
		static void decideVelocity(COMP::Transform&, COMP::Input) noexcept;

		//	Applies The Horizontal Movement To The Transform and Collision Components
		static void moveHorizontaly(COMP::Transform&, COMP::Collision&, float) noexcept;

		//	Applies The Vertical Movement To The Transform and Collision Components
		static void moveVerticaly(COMP::Transform&, COMP::Collision&, float) noexcept;

		//  After Checking The Collisions Applies The Final Transsformation of The Position
		static void ApplyMovement(Player&);

		//  Pick The Direction And The State That The Player Is In
		static void decideMovementState(Player&);
	private:
		static constexpr sf::Vector2f MAX_VELOCITY = { 600.f, -1200.f };
	};

	class Collision
	{
	public:
		//	Decide Whether The Two Shapes overlap
		static bool areIntersect(const COMP::Collision& shape_1, const COMP::Collision& shape_2) noexcept;

		//	Checks And Corrects The Horizontal Collision 
		static void processHorizontalCollision(GameWorld&);

		//	Checks And Corrects The Horizontal Collision 
		static void processVerticalCollision(GameWorld&);
	};

	class Render
	{
	public:
		//	Renders The Whole Game
		static void draw(GameWorld&, sf::RenderWindow&);
	};
}