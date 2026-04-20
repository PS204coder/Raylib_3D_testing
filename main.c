#include "raylib.h"
#include "raymath.h"


int main(){
    InitWindow(1920,1080, "window");
    
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, -100.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    Vector3 position = {0.0f, 0.0f, 0.0f};
    
    Shader shared = LoadShader("base.vs", "base.fs");
    
    Texture2D wirtuel = LoadTexture("szczor.png");
    
    Material mat = LoadMaterialDefault();
    SetMaterialTexture(&mat, 0, wirtuel);
    mat.shader = shared;
    
    
    Mesh cube = GenMeshSphere(10.0f, 30.0f, 30.0f);
    
    Vector3 rotation = {0.0f, -1.5f, 0.0f};
    
    float mouse_pos_x = GetMouseX();
    float mouse_pos_y = GetMouseY();
    
    Matrix transform = MatrixIdentity();
    transform = MatrixMultiply(transform, MatrixTranslate(0.0f, 0.0f, 0.0f));
    transform = MatrixMultiply(transform, MatrixRotateXYZ(rotation));
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        BeginDrawing();
        mouse_pos_x = GetMouseX() * -0.05f + 25;
        mouse_pos_y = GetMouseY() * -0.05f + 25;
        
        ClearBackground(BLACK);
        DrawFPS(10,10);
        
        BeginMode3D(camera);
        
        DrawMesh(cube, mat, transform);
        
        transform = MatrixIdentity();
        transform = MatrixMultiply(transform, MatrixRotateXYZ(rotation));
        transform = MatrixMultiply(transform, MatrixTranslate(mouse_pos_x, mouse_pos_y, 0.0f));
        
        //rotation = Vector3Add(rotation,(Vector3) {0.1f, 0.1f, 0.1f} );
        
//        DrawCubeWires((Vector3){0.0f, 1.0f, 0.0f},10.0f, 10.0f, 10.0f,GREEN);
        EndMode3D();
        EndDrawing();
        position = Vector3Add(position, (Vector3){0.1f, 0.1f, 0.1f});
    }
    
    CloseWindow(); 

    return 0;
}
