
#include "core/background_color.hpp"
#include "core/integrator.hpp"
#include "core/scene.hpp"

class ColorDepthIntegrator : public Integrator {
public:
  std::optional<Color> li(const Ray &ray, const Scene &scene,
                          int depth = 0) const override;
  ColorDepthIntegrator(std::unique_ptr<Camera> c, double min, double max,
                       Color n, Color f)
      : zmin{min}, zmax{max}, near{n}, far{f} {
    camera = std::move(c);
    std::cout << "Gerando um ColorDepthIntegrator" << std::endl;
  };
  void preprocess(const Scene &s) override;

private:
  double zmin;
  double zmax;

  Color near;
  Color far;
  double scene_z_min;
  double scene_z_max;
};
