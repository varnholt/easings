// Plots easing curves as ASCII art.
//
//   tinyeasings_plot                  plot all curves
//   tinyeasings_plot easeOutBounce    plot the named curves only
//   tinyeasings_plot --csv [samples]  print all curves as CSV (curve,x,y), used by tools/make_gifs.py

#include <tinyeasings/tinyeasings.hpp>

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <print>
#include <span>
#include <string>
#include <string_view>

namespace
{

constexpr int width = 60;
constexpr int height = 18;

void plot(tinyeasings::Curve curve)
{
   std::array<float, width> samples{};
   for (int column = 0; column < width; ++column)
   {
      const auto x = static_cast<float>(column) / static_cast<float>(width - 1);
      samples[static_cast<std::size_t>(column)] = tinyeasings::ease(curve, x);
   }

   // fit the y range to the curve so back/elastic overshoot stays visible
   const auto [lowest, highest] = std::ranges::minmax(samples);
   const float y_min = std::min(lowest, 0.0f);
   const float y_max = std::max(highest, 1.0f);

   const auto to_row = [&](float y)
   {
      const float t = (y_max - y) / (y_max - y_min);
      return std::clamp(static_cast<int>(std::lround(t * (height - 1))), 0, height - 1);
   };

   std::array<std::string, height> grid;
   grid.fill(std::string(width, ' '));

   // dashed guides for y = 0 and y = 1
   for (const int guide : {to_row(0.0f), to_row(1.0f)})
   {
      for (int column = 0; column < width; column += 2)
      {
         grid[static_cast<std::size_t>(guide)][static_cast<std::size_t>(column)] = '.';
      }
   }

   // connect consecutive samples with a vertical run so steep parts have no gaps
   for (int column = 0; column < width; ++column)
   {
      const int row = to_row(samples[static_cast<std::size_t>(column)]);
      const int next = column + 1 < width ? to_row(samples[static_cast<std::size_t>(column + 1)]) : row;
      const int from = std::min(row, (row + next) / 2);
      const int to = std::max(row, (row + next) / 2);

      for (int r = from; r <= to; ++r)
      {
         grid[static_cast<std::size_t>(r)][static_cast<std::size_t>(column)] = '*';
      }
   }

   std::println("{}", tinyeasings::name(curve));
   for (int row = 0; row < height; ++row)
   {
      const auto label = row == to_row(1.0f) ? "1" : row == to_row(0.0f) ? "0" : " ";
      std::println("{} |{}", label, grid[static_cast<std::size_t>(row)]);
   }
   std::println("  +{}\n", std::string(width, '-'));
}

void print_csv(int samples)
{
   std::println("curve,x,y");
   for (const auto curve : tinyeasings::all_curves)
   {
      for (int i = 0; i < samples; ++i)
      {
         const double x = static_cast<double>(i) / static_cast<double>(samples - 1);
         std::println("{},{},{}", tinyeasings::name(curve), x, tinyeasings::ease(curve, x));
      }
   }
}

}  // namespace

int main(int argc, char* argv[])
{
   const std::span args(argv + 1, static_cast<std::size_t>(argc - 1));

   if (!args.empty() && std::string_view{args[0]} == "--csv")
   {
      int samples = 61;
      if (args.size() > 1)
      {
         const std::string_view text{args[1]};
         const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), samples);
         if (error != std::errc{} || end != text.data() + text.size() || samples < 2)
         {
            std::println(stderr, "invalid sample count: {}", text);
            return 1;
         }
      }
      print_csv(samples);
      return 0;
   }

   if (args.empty())
   {
      std::ranges::for_each(tinyeasings::all_curves, plot);
      return 0;
   }

   for (const std::string_view arg : args)
   {
      const auto it = std::ranges::find(tinyeasings::all_curves, arg, tinyeasings::name);
      if (it == tinyeasings::all_curves.end())
      {
         std::println(stderr, "unknown curve: {}", arg);
         return 1;
      }
      plot(*it);
   }

   return 0;
}
