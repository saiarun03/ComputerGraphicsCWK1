#include <benchmark/benchmark.h>

#include "../draw2d/draw.hpp"
#include "../draw2d/draw-ex.hpp"
#include "../draw2d/surface-ex.hpp"

namespace
{
	// This is a placeholder. Replace this with your own code. Refer to
	// blit-benchmark/main.cpp for a more complete example. 
	void placeholder_(benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		SurfaceEx surface(width, height);
		surface.clear();

		for (auto _ : aState)
		{
			// Placeholder that just does something:
			surface.clear(); // PLACEHOLDER! EXCLUDE FROM REAL BENCHMARKS!

			// ClobberMemory() ensures that the compiler won't optimize away
			// our blit operation. (Unlikely, but technically poossible.)
			benchmark::ClobberMemory();
		}
	}

	// Horizontal Line Benchmark: A line across the width of the surface
	void draw_horizontal_line(benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		SurfaceEx surface(width, height);
		surface.clear();

		for (auto _ : aState)
		{
			// Draw a horizontal line from (0, height/2) to (width, height/2)
			draw_ex_line_solid(surface, { 0.f, static_cast<float>(height / 2) }, { static_cast<float>(width), static_cast<float>(height / 2) }, { 255, 0, 0 });

			benchmark::ClobberMemory();
		}
	}

	// Vertical Line Benchmark: A line down the middle of the surface
	void draw_vertical_line(benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		SurfaceEx surface(width, height);
		surface.clear();

		for (auto _ : aState)
		{
			// Draw a vertical line from (width/2, 0) to (width/2, height)
			draw_ex_line_solid(surface, { static_cast<float>(width / 2), 0.f }, { static_cast<float>(width / 2), static_cast<float>(height) }, { 0, 255, 0 });

			benchmark::ClobberMemory();
		}
	}

	// Diagonal Line (45-degree) Benchmark: A diagonal line from top-left to bottom-right
	void draw_diagonal_line(benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		SurfaceEx surface(width, height);
		surface.clear();

		for (auto _ : aState)
		{
			// Draw a diagonal line from (0, 0) to (width, height)
			draw_ex_line_solid(surface, { 0.f, 0.f }, { static_cast<float>(width), static_cast<float>(height) }, { 0, 0, 255 });

			benchmark::ClobberMemory();
		}
	}

	// Thick Line Benchmark: A thicker line from (100, 100) to (width, height)
	void draw_thick_line(benchmark::State& aState)
	{
		auto const width = std::uint32_t(aState.range(0));
		auto const height = std::uint32_t(aState.range(1));

		SurfaceEx surface(width, height);
		surface.clear();

		for (auto _ : aState)
		{
			// Draw a thick line (5 pixels wide) from (100, 100) to (width, height)
			draw_ex_line_solid(surface, { 100.f, 100.f }, { static_cast<float>(width), static_cast<float>(height) }, { 255, 255, 0 });

			benchmark::ClobberMemory();
		}
	}
}

BENCHMARK(placeholder_)
	->Args({ 1920, 1080 })
	->Args({ 7680, 4320 });

BENCHMARK(draw_horizontal_line)
	->Args({ 1920, 1080 })
	->Args({ 7680, 4320 });

BENCHMARK(draw_vertical_line)
	->Args({ 1920, 1080 })
	->Args({ 7680, 4320 });

BENCHMARK(draw_diagonal_line)
	->Args({ 1920, 1080 })
	->Args({ 7680, 4320 });

BENCHMARK(draw_thick_line)
	->Args({ 1920, 1080 })
	->Args({ 7680, 4320 });

BENCHMARK_MAIN();
