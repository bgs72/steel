Perform next steps to install the systemd scripts:

  mkdir -p ~/.config/systemd/system
  cp *.service ~/.config/systemd/system
  cd ~/.config/systemd/system
  sudo systemctl link ./steel.service
  sudo systemctl link ./steel-resume.service
  sudo systemctl enable --now ./steel.service
  sudo systemctl enable --now ./steel-resume.service

