#include "days.hpp"

#include <range/v3/all.hpp>
#include "input_utils.hpp"
#include "lexical_cast.hpp"

struct instruction
{
  enum class operation { nop, acc, jmp, num };
  operation op;
  int value;
};

std::array<std::string_view, static_cast<size_t>(instruction::operation::num)>
  ops{
  "nop",
  "acc",
  "jmp"
};

using instructions = std::vector<instruction>;

auto parse_instructions(std::istream &input) -> instructions
{
  instructions instructions;
  std::string op_str;
  std::string val_str;

  while (input >> op_str && input >> val_str) {
    auto const op = static_cast<instruction::operation>(
      std::distance(ops.begin(), ranges::find(ops, op_str)));
    instruction inst{ op, utils::lexical_cast<int>(val_str) };
    instructions.push_back(inst);
  }
  return instructions;
}

auto run_instructions(const instructions &instructions) -> std::pair<int, bool>
{
  int accumulator = 0;
  size_t current_pos = 0;
  std::vector<bool> already_run(instructions.size(), false);
  while (current_pos < instructions.size() && already_run[current_pos] == false) {
    already_run[current_pos] = true;
    auto const current = instructions[current_pos];
    switch (current.op) {
    case instruction::operation::nop:
      ++current_pos;
      break;
    case instruction::operation::acc:
      accumulator += current.value;
      ++current_pos;
      break;
    case instruction::operation::jmp:
      current_pos += current.value;
      break;
    case instruction::operation::num:
    default:
      break;
    }
  }
  return { accumulator, current_pos == instructions.size()};
}

template<>
auto days::solve<days::day::day_8, days::part::part_1>(std::istream &input)
  -> std::string
{
  auto const instructions = parse_instructions(input);
  auto const result = run_instructions(instructions);
  return std::to_string(result.first);
}

template<>
auto days::solve<days::day::day_8, days::part::part_2>(std::istream &input)
  -> std::string
{
  auto instructions = parse_instructions(input);
  int accumulator = 0;
  for (size_t n = 0; n < instructions.size(); ++n) {
    if (instructions[n].op == instruction::operation::nop) {
      instructions[n].op = instruction::operation::jmp;
      const auto result = run_instructions(instructions);
      if (result.second == true) {
        accumulator = result.first;
        break;
      }
      instructions[n].op = instruction::operation::nop;
    } else if (instructions[n].op == instruction::operation::jmp) {
      instructions[n].op = instruction::operation::nop;
      const auto result = run_instructions(instructions);
      if (result.second == true) {
        accumulator = result.first;
        break;
      }
      instructions[n].op = instruction::operation::jmp;
    }
  }

  return std::to_string(accumulator);
}