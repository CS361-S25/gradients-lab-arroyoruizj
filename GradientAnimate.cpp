#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/Random.hpp"

emp::web::Document doc{"target"};

class GradientAnimator : public emp::web::Animate {

    double gridSize = 1000;
    int cellSize = 100;
    float number = 0;
    int startCells = 5;

    std::vector<std::vector<float>> cells;
    emp::web::Canvas canvas{gridSize, gridSize, "canvas"};

    public:

        GradientAnimator() {

            doc << canvas;
            doc << GetToggleButton("Toggle");
            doc << GetStepButton("Step");

            for (int x = 0; x < 10; x++) {

                for (int y = 0; y < 10; y++) {

                    canvas.Rect(x * cellSize, y * cellSize, cellSize, cellSize, "white", "black");

                }
            }

            cells.resize(10, std::vector<float>(10, 0));

            emp::Random random_gen(123);

            for (int r = 0; r < startCells; r++) {

                int randX = random_gen.GetInt(0, 10); // Corrected range to include 10
                int randY = random_gen.GetInt(0, 10); // Corrected range to include 10
                int randVal = random_gen.GetInt(0, 244);

                cells[randX][randY] = 1;
            }
            
        }

        float FindNeighborsAvg(int x, int y) {
            // This function will find the neighbors of a cell
            // and update the canvas accordingly

            float total = 0;

            int leftmostX = emp::Mod(x - 1, cellSize);
            int rightmostX = emp::Mod(x + 1, cellSize);

            int leftmostY = emp::Mod(y - 1, cellSize);
            int rightmostY = emp::Mod(y + 1, cellSize);

            for (int i = leftmostX; i <= rightmostX; i++) {

                for (int j = leftmostY; j <= rightmostY; j++) {

                    total = total + cells[i][j];
                }
            }

            return total / 9;
        }

        void DoFrame() {

            canvas.Clear();

            std::vector<std::vector<float>> NewCells;
            NewCells.resize(10, std::vector<float>(10, 0));

            for (int i = 0; i < 10; i++) {

                for (int j = 0; j < 10; j++) {

                    float cellValue = FindNeighborsAvg(i, j);
                    NewCells[i][j] = cellValue;
                    canvas.Rect(i * cellSize, j * cellSize, cellSize, cellSize, emp::ColorHSV(0, 0, cellValue), "black");

                }
            }

            cells = NewCells;
        }
};

GradientAnimator animator;

int main() {

    return 0;

}