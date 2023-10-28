import pygame
import random
import sys

class Vector2():
    def __init__(self,x,y) -> None:
        self.x = x
        self.y = y

# Constants
SPEED = 10
BALL_RADIUS = 5

player_score = 0

screenWidth = 450
screenHeight = 800

# Initialize Pygame
pygame.init()
clock = pygame.time.Clock()
# Create the game window
screen = pygame.display.set_mode((screenWidth, screenHeight))
pygame.display.set_caption("Pygame Example")

# Player rectangle
player = pygame.Rect(screenWidth // 2, 600, 80, 10)

# Ball properties
ballPos = Vector2(screenWidth // 2, screenHeight // 2)
ballSpeed = Vector2(0, -10)

def game_step(action ):
    global player_score, ballPos, ballSpeed

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # keys = pygame.key.get_pressed()
    # if keys[pygame.K_a]:
    #     player.x -= SPEED
    # if keys[pygame.K_d]:
    #     player.x += SPEED
    if action[0] == 1:
        player.x += SPEED
    elif action[1] == 1:
        player.x -= SPEED

        


    ballPos = Vector2(ballPos.x + ballSpeed.x, ballPos.y + ballSpeed.y)

    if (player.x + player.width) >= screenWidth:
        player.x = screenWidth - player.width
    elif player.x <= 0:
        player.x = 0

    reward = 0

    if (ballPos.y + BALL_RADIUS) >= screenHeight:
        ballSpeed.y = - ballSpeed.y;
        ballPos = Vector2(ballPos.x, screenHeight - BALL_RADIUS)
    if ballPos.y - BALL_RADIUS <= 0:
        player_score += 1
        reward = 1
        ballSpeed.y = - ballSpeed.y;

    if ballPos.x - BALL_RADIUS <= 0:
        ballSpeed.x = - ballSpeed.x;
    elif ballPos.x + BALL_RADIUS >= screenWidth:
        ballSpeed.x = - ballSpeed.x;

    if ballPos.y >= player.y + 70:
        reward = -10

    # Ball collision
    player_rect = pygame.Rect(player.x, player.y, player.width, player.height)
    if player_rect.colliderect((ballPos.x - BALL_RADIUS, ballPos.y - BALL_RADIUS, BALL_RADIUS * 2, BALL_RADIUS * 2)):
        playerCenter = player.x + (player.width / 2)
        d = (playerCenter - ballPos.x) 
        ballSpeed = Vector2( d * -0.1, -ballSpeed.y)
        reward +=10
        player_score += 10

    # Clear the screen
    screen.fill((255, 255, 255))

    # Draw player
    pygame.draw.rect(screen, (0, 0, 255), player)

    # Draw ball
    pygame.draw.circle(screen, (0, 0, 0), (ballPos.x, ballPos.y), BALL_RADIUS)

    # Draw player score
    font = pygame.font.Font(None, 36)
    score_text = font.render(f"Player Score: {player_score}", True, (0, 0, 0))
    screen.blit(score_text, (10, 10))

    pygame.display.flip()
    clock.tick(60)  # limits FPS to 60
    return reward, reward <0, player_score

def reset():
    global player_score,ballPos,ballSpeed,player
    player_score=0
    ballPos = Vector2(screenWidth // 2, screenHeight // 2)
    ballSpeed = Vector2(random.randint(-5,5), -10)
    player.x = screenWidth /2



# Main game loop
# while True:
#     game_step()
