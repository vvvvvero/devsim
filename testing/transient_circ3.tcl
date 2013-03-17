# Copyright 2013 Devsim LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# ssac circuit only
circuit_element -name V1 -n1 1 -n2 0 -value 1.0 -acreal 1.0
#lambda = 0.04
circuit_element -name R1 -n1 1 -n2 2 -value 5
circuit_element -name C1 -n1 2 -n2 0 -value 5

puts "transient_dc"
solve -type transient_dc   -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3
circuit_alter -name V1 -value 0.0

set gamma [expr 2 - sqrt(2.0)];
puts "transient_tr, transient_bdf2"
solve -type transient_tr   -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_bdf2 -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_tr   -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_bdf2 -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_tr   -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_bdf2 -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_tr   -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_bdf2 -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_tr   -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2
solve -type transient_bdf2 -absolute_error 1.0 -relative_error 1e-14 -maximum_iterations 3 -tdelta 1e-3 -gamma $gamma -charge_error 1e-2

