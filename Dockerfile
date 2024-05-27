from ubuntu

run apt -qq update || apt update
run apt-get update
run apt-get -qq install devscripts equivs software-properties-common
#run apt install -q python3-pip python3-setuptools python3-dev python3-wheel build-essential libssl-dev libffi-dev
run apt-get install -y python3-full
run apt-get install -y python3-pip
#run python3 -m pip install "urllib3<2.0.0"
run python3 -m pip install --upgrade -q setuptools wheel pip
run python3 -m pip install cloudsmith-cli cryptography cmake




