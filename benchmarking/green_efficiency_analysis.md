# Green Efficiency Analysis

## Measurement Methodology

The execution time of the program was measured using the `clock()` function from `<time.h>`. CPU time was recorded before and after each major phase of the program. The measured phases were:

- Dataset construction (`build_dataset`)
- Dataset processing (`process_dataset`)
- Checksum reduction (`reduce_checksum`)

The total runtime was also measured by placing timers around the complete sequence of operations. All clock values were converted to seconds using `CLOCKS_PER_SEC`.

The measured output from the program was:

- TOTAL seconds: 0.000790
- BUILD_DATA seconds: 0.000313
- PROCESS seconds: 0.000331
- REDUCE seconds: 0.000139

These measurements were collected without changing the program logic. Only timing instrumentation was added.

## Observed Performance Differences

The measurements show that the processing stage consumed the largest amount of execution time.

The dataset construction phase required approximately 0.000313 seconds because it generated 50,000 pseudo-random values and stored them in memory.

The processing phase required approximately 0.000331 seconds. This phase performed multiple arithmetic operations and conditional checks on every element of the dataset, making it the most computationally expensive stage.

The checksum reduction phase required only about 0.000139 seconds. Although it also iterated through the dataset, it performed fewer operations for each element, resulting in the shortest execution time.

The total execution time was slightly greater than the sum of the individual phases because timing itself introduces a small overhead.

## Relation Between Runtime and Energy Consumption

Execution time and energy consumption are closely related. A program that spends more CPU time generally consumes more energy because the processor remains active for longer periods.

The measurements indicate that the processing phase is responsible for the largest share of runtime. Therefore, optimizing this phase would likely provide the greatest reduction in both execution time and energy usage.

Reducing unnecessary calculations, improving algorithms, or minimizing repeated operations can improve efficiency while lowering energy consumption.

## Limitations of the Experiment

This experiment has several limitations.

The measured execution times are extremely small, making them sensitive to system scheduling, processor frequency changes, and measurement overhead.

The experiment was executed only once under a single environment. Running the program multiple times and averaging the results would provide more reliable measurements.

In addition, the experiment measures CPU execution time rather than actual electrical energy consumption. Runtime is only an indirect indicator of energy efficiency.

## Practical Engineering Takeaway

This experiment demonstrates that measuring execution time helps identify where a program spends most of its work. The collected data shows that the processing stage dominates the runtime and therefore represents the best target for optimization.

Performance improvements should be based on measured evidence rather than assumptions. Even simple timing instrumentation can reveal which parts of a program deserve optimization effort.

Using systematic measurements before making changes is an important engineering practice because it allows developers to improve software performance while also supporting more energy-efficient computing.
