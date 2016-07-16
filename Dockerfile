FROM  debian:latest

# Credit goes to https://github.com/headstar/sphinx-doc-docker

RUN   apt-get update

RUN   DEBIAN_FRONTEND=noninteractive apt-get install -y python-pip
RUN   DEBIAN_FRONTEND=noninteractive apt-get install -y texlive texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended
RUN   DEBIAN_FRONTEND=noninteractive apt-get install -y enchant
RUN   apt-get update --fix-missing
RUN   DEBIAN_FRONTEND=noninteractive apt-get install -y git

RUN   pip install Sphinx==1.4
RUN   pip install sphinx_rtd_theme
RUN   pip install alabaster
RUN   pip install sphinx_bootstrap_theme

CMD ["/bin/bash"]