#include <raylib.h>

int playerX = 20;
int playerY = 152;
int jumpFor = 0;
int playerMovementY = 0;
int gravity = 15;
int stopingTimer = 0;

float bgforeX_1 = 0.0;
float bgforeX_2 = 0.0;
float bgforeX_3 = 0.0;

float bgmidX_1 = 0.0;
float bgmidX_2 = 512.0;
float bgmidX_3 = 1024.0;
float bgmidX_4 = 1536.0;

float bgbackX_1 = 0.0;
float bgbackX_2 = 512.0;
float bgbackX_3 = 1024.0;
float bgbackX_4 = 1536.0;

bool jumpReady = true;
bool stopingDelayRight = false;
bool stopingDelayLeft = false;
bool grounded = true;

void JUMP(){

	if(IsKeyPressed(KEY_W) && jumpReady){
		playerMovementY -= 15;
		jumpFor = 10;
		gravity = 0;
		jumpReady = false;
	}

	if(jumpFor > 0){
		jumpFor -= 1;
	}
	else{
		playerMovementY = 0;
		gravity = 15;
	}

	playerY += playerMovementY + gravity;

	if(playerY >= 152){
		playerY = 152;
		jumpReady = true;
        grounded = true;
	}

}

void move_right(float width_of_char){
	if(IsKeyDown(KEY_D) && playerX < ((1080) - ((width_of_char) + 20))){
		playerX += 10;
        stopingDelayLeft = false;
	}
    if(IsKeyReleased(KEY_D)){
        stopingDelayRight = true;
    }
    if(stopingDelayRight && !IsKeyDown(KEY_A) && grounded && playerX < (((1080) - ((width_of_char) + 20)) - 50)){
        playerX += 5;
        stopingTimer ++;
    }
    if(stopingTimer == 10){
        stopingDelayRight = false;
        stopingTimer = 0;
    }
}

void move_left(){
	if(IsKeyDown(KEY_A) && playerX > 20){
		playerX -= 10;
        stopingDelayRight = false;
	}
    if(IsKeyReleased(KEY_A)){
        stopingDelayLeft = true;
    }
    if(stopingDelayLeft && !IsKeyDown(KEY_D) && grounded && playerX > (20 + 50)){
        playerX -= 5;
        stopingTimer ++;
    }
    if(stopingTimer == 10){
        stopingDelayLeft = false;
        stopingTimer = 0;
    }
}

void main(void){


    int FPS = 60;

    //int window_height = GetScreenHeight();
    //int window_width = GetScreenWidth();

    InitWindow(1080, 282, "Test");

    SetTargetFPS(FPS);

    Texture2D scarfy = LoadTexture("./assets/scarfy.png");
    Texture2D bgfore = LoadTexture("./assets/bgfore.png");
    Texture2D bgmid = LoadTexture("./assets/bgmid.png");
    Texture2D bgback = LoadTexture("./assets/bgback.png");

    bgforeX_2 = bgfore.width;
    bgforeX_3 = 2*bgfore.width;

    float frame_width = (float)(scarfy.width / 6); //     /6 because there are 6 frames
    int MaxFramesImg = (int)(scarfy.width / (int)frame_width);

    float timer = 0.0;
    int ImgFrame = 0;


    do{
        timer += GetFrameTime(); //GetFrameTime is to get the velue of time used to render 1 frame

        if(timer >= 0.15){
            timer = 0.0;
            ImgFrame += 1;
        }

        ImgFrame = ImgFrame % MaxFramesImg; //this will count upto maxframes - 1 then loop

        bgforeX_1 -= 6.5;
        bgforeX_2 -= 6.5;
        bgforeX_3 -= 6.5;

        if(bgforeX_1 <= -bgfore.width){
            bgforeX_1 = (2*bgfore.width) + (bgforeX_1 + bgfore.width);
            }

        if(bgforeX_2 <= -bgfore.width){
            bgforeX_2 = (2*bgfore.width) + (bgforeX_2 + bgfore.width);
            }

        if(bgforeX_3 <= -bgfore.width){
            bgforeX_3 = (2*bgfore.width) + (bgforeX_3 + bgfore.width);
            }

        bgmidX_1 -= 4;
        bgmidX_2 -= 4;
        bgmidX_3 -= 4;
        bgmidX_4 -= 4;

        if(bgmidX_1 <= -(bgmid.width)){
            bgmidX_1 = (3*bgmid.width) + (bgmidX_1 + bgmid.width);
        }

        if(bgmidX_2 <= -(bgmid.width)){
            bgmidX_2 = (3*bgmid.width) + (bgmidX_2 + bgmid.width);
        }

        if(bgmidX_3 <= -(bgmid.width)){
            bgmidX_3 = (3*bgmid.width) + (bgmidX_3 + bgmid.width);
        }

        if(bgmidX_4 <= -(bgmid.width)){
            bgmidX_4 = (3*bgmid.width) + (bgmidX_4 + bgmid.width);
        }

        bgbackX_1 -= 3;
        bgbackX_2 -= 3;
        bgbackX_3 -= 3;
        bgbackX_4 -= 3;

        if(bgbackX_1 <= -(bgback.width)){
            bgbackX_1 = (3*bgback.width) + (bgbackX_1 + bgback.width);
        }

        if(bgbackX_2 <= -(bgback.width)){
            bgbackX_2 = (3*bgback.width) + (bgbackX_2 + bgback.width);
        }

        if(bgbackX_3 <= -(bgback.width)){
            bgbackX_3 = (3*bgback.width) + (bgbackX_3 + bgback.width);
        }

        if(bgbackX_4 <= -(bgback.width)){
            bgbackX_4 = (3*bgback.width) + (bgbackX_4 + bgback.width);
        }

        BeginDrawing();

            ClearBackground(GRAY);

            JUMP();
            move_left();
            move_right(frame_width);

            DrawTexture(bgback, bgbackX_1, 0, RAYWHITE);
            DrawTexture(bgback, bgbackX_2, 0, RAYWHITE);
            DrawTexture(bgback, bgbackX_3, 0, RAYWHITE);
            DrawTexture(bgback, bgbackX_4, 0, RAYWHITE);

            DrawTexture(bgmid, bgmidX_1, 44, RAYWHITE);
            DrawTexture(bgmid, bgmidX_2, 44, RAYWHITE);
            DrawTexture(bgmid, bgmidX_3, 44, RAYWHITE);
            DrawTexture(bgmid, bgmidX_4, 44, RAYWHITE);

            DrawTexture(bgfore, bgforeX_1, 90, RAYWHITE);
            DrawTexture(bgfore, bgforeX_2, 90, RAYWHITE);
            DrawTexture(bgfore, bgforeX_3, 90, RAYWHITE);


            DrawTextureRec(
                scarfy,
                (Rectangle){(frame_width * ImgFrame), 0, frame_width, (float)scarfy.height}, // x, y coordinates on the image to be drawn are the first two parameters
                (Vector2){playerX, playerY},
                RAYWHITE); //this will draw a specific part of the image

            DrawFPS(1055, 720);

        EndDrawing();

    }while(!WindowShouldClose());

    CloseWindow();
}
