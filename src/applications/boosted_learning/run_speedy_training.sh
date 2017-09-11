#!/bin/sh

set -x  # will print excecuted commands

echo "Launching training"

./boosted_learning -c inria_speedy_training_config.ini

echo "Training finished."

