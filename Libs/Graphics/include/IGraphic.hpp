/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IGraphic
*/

#pragma once

#include <vector>
#include <cstdint>

namespace Graphics {
    // Color type, RGBA (32bit)
    typedef struct Color {
        unsigned char r;        // Color red value
        unsigned char g;        // Color green value
        unsigned char b;        // Color blue value
        unsigned char a;        // Color alpha value
    } Color;

    // Mouse buttons enum
    typedef enum {
        MOUSE_BUTTON_LEFT    = 0,       // Mouse button left
        MOUSE_BUTTON_RIGHT   = 1,       // Mouse button right
        MOUSE_BUTTON_MIDDLE  = 2,       // Mouse button middle (pressed wheel)
        MOUSE_BUTTON_SIDE    = 3,       // Mouse button side (advanced mouse device)
        MOUSE_BUTTON_EXTRA   = 4,       // Mouse button extra (advanced mouse device)
        MOUSE_BUTTON_FORWARD = 5,       // Mouse button forward (advanced mouse device)
        MOUSE_BUTTON_BACK    = 6,       // Mouse button back (advanced mouse device)
    } MouseButton;

    // Keyboard keys (US keyboard layout) enum
    typedef enum {
        KEY_NULL            = 0,        // Key: NULL, used for no key pressed
        // Alphanumeric keys
        KEY_APOSTROPHE      = 39,       // Key: '
        KEY_COMMA           = 44,       // Key: ,
        KEY_MINUS           = 45,       // Key: -
        KEY_PERIOD          = 46,       // Key: .
        KEY_SLASH           = 47,       // Key: /
        KEY_ZERO            = 48,       // Key: 0
        KEY_ONE             = 49,       // Key: 1
        KEY_TWO             = 50,       // Key: 2
        KEY_THREE           = 51,       // Key: 3
        KEY_FOUR            = 52,       // Key: 4
        KEY_FIVE            = 53,       // Key: 5
        KEY_SIX             = 54,       // Key: 6
        KEY_SEVEN           = 55,       // Key: 7
        KEY_EIGHT           = 56,       // Key: 8
        KEY_NINE            = 57,       // Key: 9
        KEY_SEMICOLON       = 59,       // Key: ;
        KEY_EQUAL           = 61,       // Key: =
        KEY_A               = 65,       // Key: A | a
        KEY_B               = 66,       // Key: B | b
        KEY_C               = 67,       // Key: C | c
        KEY_D               = 68,       // Key: D | d
        KEY_E               = 69,       // Key: E | e
        KEY_F               = 70,       // Key: F | f
        KEY_G               = 71,       // Key: G | g
        KEY_H               = 72,       // Key: H | h
        KEY_I               = 73,       // Key: I | i
        KEY_J               = 74,       // Key: J | j
        KEY_K               = 75,       // Key: K | k
        KEY_L               = 76,       // Key: L | l
        KEY_M               = 77,       // Key: M | m
        KEY_N               = 78,       // Key: N | n
        KEY_O               = 79,       // Key: O | o
        KEY_P               = 80,       // Key: P | p
        KEY_Q               = 81,       // Key: Q | q
        KEY_R               = 82,       // Key: R | r
        KEY_S               = 83,       // Key: S | s
        KEY_T               = 84,       // Key: T | t
        KEY_U               = 85,       // Key: U | u
        KEY_V               = 86,       // Key: V | v
        KEY_W               = 87,       // Key: W | w
        KEY_X               = 88,       // Key: X | x
        KEY_Y               = 89,       // Key: Y | y
        KEY_Z               = 90,       // Key: Z | z
        KEY_LEFT_BRACKET    = 91,       // Key: [
        KEY_BACKSLASH       = 92,       // Key: '\'
        KEY_RIGHT_BRACKET   = 93,       // Key: ]
        KEY_GRAVE           = 96,       // Key: `
        // Function keys
        KEY_SPACE           = 32,       // Key: Space
        KEY_ESCAPE          = 256,      // Key: Esc
        KEY_ENTER           = 257,      // Key: Enter
        KEY_TAB             = 258,      // Key: Tab
        KEY_BACKSPACE       = 259,      // Key: Backspace
        KEY_INSERT          = 260,      // Key: Ins
        KEY_DELETE          = 261,      // Key: Del
        KEY_RIGHT           = 262,      // Key: Cursor right
        KEY_LEFT            = 263,      // Key: Cursor left
        KEY_DOWN            = 264,      // Key: Cursor down
        KEY_UP              = 265,      // Key: Cursor up
        KEY_PAGE_UP         = 266,      // Key: Page up
        KEY_PAGE_DOWN       = 267,      // Key: Page down
        KEY_HOME            = 268,      // Key: Home
        KEY_END             = 269,      // Key: End
        KEY_CAPS_LOCK       = 280,      // Key: Caps lock
        KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
        KEY_NUM_LOCK        = 282,      // Key: Num lock
        KEY_PRINT_SCREEN    = 283,      // Key: Print screen
        KEY_PAUSE           = 284,      // Key: Pause
        KEY_F1              = 290,      // Key: F1
        KEY_F2              = 291,      // Key: F2
        KEY_F3              = 292,      // Key: F3
        KEY_F4              = 293,      // Key: F4
        KEY_F5              = 294,      // Key: F5
        KEY_F6              = 295,      // Key: F6
        KEY_F7              = 296,      // Key: F7
        KEY_F8              = 297,      // Key: F8
        KEY_F9              = 298,      // Key: F9
        KEY_F10             = 299,      // Key: F10
        KEY_F11             = 300,      // Key: F11
        KEY_F12             = 301,      // Key: F12
        KEY_LEFT_SHIFT      = 340,      // Key: Shift left
        KEY_LEFT_CONTROL    = 341,      // Key: Control left
        KEY_LEFT_ALT        = 342,      // Key: Alt left
        KEY_LEFT_SUPER      = 343,      // Key: Super left
        KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
        KEY_RIGHT_CONTROL   = 345,      // Key: Control right
        KEY_RIGHT_ALT       = 346,      // Key: Alt right
        KEY_RIGHT_SUPER     = 347,      // Key: Super right
        KEY_KB_MENU         = 348,      // Key: KB menu
        // Keypad keys
        KEY_KP_0            = 320,      // Key: Keypad 0
        KEY_KP_1            = 321,      // Key: Keypad 1
        KEY_KP_2            = 322,      // Key: Keypad 2
        KEY_KP_3            = 323,      // Key: Keypad 3
        KEY_KP_4            = 324,      // Key: Keypad 4
        KEY_KP_5            = 325,      // Key: Keypad 5
        KEY_KP_6            = 326,      // Key: Keypad 6
        KEY_KP_7            = 327,      // Key: Keypad 7
        KEY_KP_8            = 328,      // Key: Keypad 8
        KEY_KP_9            = 329,      // Key: Keypad 9
        KEY_KP_DECIMAL      = 330,      // Key: Keypad .
        KEY_KP_DIVIDE       = 331,      // Key: Keypad /
        KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
        KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
        KEY_KP_ADD          = 334,      // Key: Keypad +
        KEY_KP_ENTER        = 335,      // Key: Keypad Enter
        KEY_KP_EQUAL        = 336,      // Key: Keypad =
        // Android key buttons
        KEY_BACK            = 4,        // Key: Android back button
        KEY_MENU            = 5,        // Key: Android menu button
        KEY_VOLUME_UP       = 24,       // Key: Android volume up button
        KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
    } KeyboardInput;

    /// @brief Struct that define a star for the background
    /// @param x The x position of the star
    /// @param y The y position of the star
    /// @param size The size of the star
    /// @param color The color of the star
    struct Star {
        float x; // The x position of the star
        float y; // The y position of the star
        int size; // Size of the star
        Color color; // Color of the star
    };

    /**
     * @brief Type alias for an entity identifier.
     * 
     * An entity is an object in the ECS system. It is represented by a unique identifier.
     */
    using Entity = std::uint32_t;

    /**
     * @brief Maximum number of entities.
     * 
     * This constant defines the maximum number of entities that can be created in the ECS system.
     */
    const Entity MAX_ENTITIES = 1000;

    /**
     * @brief Vector2 type
     * 
     * This struct represents a 2D vector.
     */
    typedef struct Rectangle {
        float x;                // Rectangle top-left corner position x
        float y;                // Rectangle top-left corner position y
        float width;            // Rectangle width
        float height;           // Rectangle height
    } Rectangle;

    /**
     * @brief Vector2 type
     * 
     * This struct represents a 2D vector.
     */
    typedef struct Vector2 {
        float x;                // Vector x component
        float y;                // Vector y component
    } Vector2;

    /**
     * @brief Interface for the graphics system
     * 
     * This interface provides functions to initialize the graphics system, render shapes, text, and textures,
     * handle input, and manage the window.
     */
    class IGraphic {
        public:
            /**
             * @brief Destroy the IGraphic object
             */
            virtual ~IGraphic() = default;

            /**
             * @brief Initialize the graphics
             * 
             * This function initializes the graphics system with the given title.
             * Also initializes the audio device, toggles fullscreen, and sets the exit key.
             * 
             * @param title 
             */
            virtual void InitGraphics(const char *title) = 0;

            /**
             * @brief Close the graphics
             * 
             * Closes the window and the audio device.
             * 
             */
            virtual void CloseGraphics() = 0;

            /**
             * @brief Get the Window Width
             * 
             * @return The window width
             */
            virtual int GetWindowWidth() = 0;

            /**
             * @brief Get the Window Height 
             * 
             * @return The window height
             */
            virtual int GetWindowHeight() = 0;

            /**
             * @brief Render a circle
             * 
             * @param x The x position of the circle
             * @param y The y position of the circle
             * @param radius The radius of the circle
             * @param color The color of the circle
             */
            virtual void RenderCircle(int x, int y, int radius, Color color) = 0;

            /**
             * @brief Render a rectangle
             * 
             * @param posX The x position of the rectangle
             * @param posY The y position of the rectangle
             * @param width The width of the rectangle
             * @param height The height of the rectangle
             * @param color The color of the rectangle
             */
            virtual void RenderRectangle(int posX, int posY, int width, int height, Color color) = 0;

            /**
             * @brief Render a rounded rectangle
             * 
             * @param rec The rectangle to render
             * @param roundness The roundness of the rectangle
             * @param segments The number of segments
             * @param color The color of the rectangle
             */
            virtual void RenderRoundedRectangle(Rectangle rec, float roundness, int segments, Color color) = 0;

            /**
             * @brief Render the sides of a rounded rectangle
             * 
             * @param rec The rectangle to render
             * @param roundness The roundness of the rectangle
             * @param segments The number of segments
             * @param color The color of the rectangle
             */
            virtual void RenderRoundedRectangleSides(Rectangle rec, float roundness, int segments, Color color) = 0;

            /**
             * @brief Render text
             * 
             * @param text The text to render
             * @param posX The x position of the text
             * @param posY The y position of the text
             * @param fontSize The font size of the text
             * @param color The color of the text
             */
            virtual void RenderText(const char *text, int posX, int posY, int fontSize, Color color) = 0;

            /**
             * @brief Get the size of the text
             * 
             * @param text The text to get the size of
             * @param fontSize The font size of the text
             * 
             * @return The size of the text
             */
            virtual int TextSize(const char *text, int fontSize) = 0;

            /**
             * @brief Get the cursor position
             * 
             * @return The cursor position
             */
            virtual Vector2 GetCursorPosition() = 0;

            /**
             * @brief Check if the mouse is colliding with a rectangle
             * 
             * @param point The point to check
             * @param rec The rectangle to check
             * 
             * @return True if the mouse is colliding with the rectangle, false otherwise
             */
            virtual bool CheckCollisionMouse(Vector2 point, Rectangle rec) = 0;

            /**
             * @brief Check if a mouse button is clicked
             * 
             * @param button The button to check
             * 
             * @return True if the button is clicked, false otherwise
             */
            virtual bool IsMouseButtonClicked(int button) = 0;

            /**
             * @brief Render a texture
             * 
             * @param Id The unique identifier of the texture
             * @param posX The x position of the texture
             * @param posY The y position of the texture
             * @param tint The color of the texture
             */
            virtual void RenderPreciseTexture(int Id, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) = 0;

            /**
             * @brief Render the frames per second
             * 
             * @param posX The x position of the FPS
             * @param posY The y position of the FPS
             */
            virtual void RenderFPS(int posX, int posY) = 0;

            /**
             * @brief Start rendering
             */
            virtual void StartRendering() = 0;

            /**
             * @brief End rendering
             */
            virtual void EndRendering() = 0;

            /**
             * @brief Clear the screen
             * 
             * @param color The color to clear the screen with
             */
            virtual void ResetBackground(Color color) = 0;

            /**
             * @brief Check if an input is pressed
             * 
             * @param key The key to check
             * 
             * @return True if the key is pressed, false otherwise
             */
            virtual bool IsInputPressed(int key) = 0;

            /**
             * @brief Set the window resolution
             * 
             * @param width The width of the window
             * @param height The height of the window
             */
            virtual void SetWindowResolution(int width, int height) = 0;

            /**
             * @brief Set the frames per second
             * 
             * @param fps The frames per second
             */
            virtual void SetFPS(int fps) = 0;

            /**
             * @brief Fade a color
             * 
             * @param color The color to fade
             * @param alpha The alpha value
             * 
             * @return The faded color
             */
            virtual Color FadeColor(Color color, float alpha) = 0;

            /**
             * @brief Check if the window is closing
             * 
             * @return True if the window is closing, false otherwise
             */
            virtual bool IsWindowClosing() = 0;

            /**
             * @brief Load a texture from a file
             * 
             * @param Id The unique identifier of the texture
             * @param filename The filename of the texture
             */
            virtual void LoadTextureFromFile(int Id, const char *filename) = 0;

            /**
             * @brief Unload a texture by its unique identifier
             * 
             * @param Id The unique identifier of the texture
             */
            virtual void UnloadTextureById(int Id) = 0;
        protected:
        private:
    };
} // namespace Graphics

#undef LIGHTGRAY
#undef GRAY
#undef DARKGRAY
#undef YELLOW
#undef GOLD
#undef ORANGE
#undef PINK
#undef RED
#undef MAROON
#undef GREEN
#undef LIME
#undef DARKGREEN
#undef SKYBLUE
#undef BLUE
#undef DARKBLUE
#undef PURPLE
#undef VIOLET
#undef DARKPURPLE
#undef BEIGE
#undef BROWN
#undef DARKBROWN
#undef WHITE
#undef BLACK
#undef BLANK
#undef MAGENTA

#define LIGHTGRAY  (Color){ 200, 200, 200, 255 }   // Light Gray
#define GRAY       (Color){ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   (Color){ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     (Color){ 253, 249, 0, 255 }     // Yellow
#define GOLD       (Color){ 255, 203, 0, 255 }     // Gold
#define ORANGE     (Color){ 255, 161, 0, 255 }     // Orange
#define PINK       (Color){ 255, 109, 194, 255 }   // Pink
#define RED        (Color){ 230, 41, 55, 255 }     // Red
#define MAROON     (Color){ 190, 33, 55, 255 }     // Maroon
#define GREEN      (Color){ 0, 228, 48, 255 }      // Green
#define LIME       (Color){ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  (Color){ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    (Color){ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       (Color){ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   (Color){ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     (Color){ 200, 122, 255, 255 }   // Purple
#define VIOLET     (Color){ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE (Color){ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      (Color){ 211, 176, 131, 255 }   // Beige
#define BROWN      (Color){ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  (Color){ 76, 63, 47, 255 }      // Dark Brown
#define WHITE      (Color){ 255, 255, 255, 255 }   // White
#define BLACK      (Color){ 0, 0, 0, 255 }         // Black
#define BLANK      (Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    (Color){ 255, 0, 255, 255 }     // Magenta
