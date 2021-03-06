# SPDX-FileCopyrightText: 2020 Efabless Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# SPDX-License-Identifier: Apache-2.0

drc off
gds readonly true
gds read ../gds/sram_1rw1r_32_256_8_sky130_lp1.gds
load openram_tc_1kb.mag
select top cell
move origin -1015um -1272.5um
box position 0 0
getcell advSeal_6um_gen
save
gds write ../gds/openram_tc_1kb.gds

