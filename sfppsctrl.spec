Name:		sfppsctrl
Version:	1.0
Release:	1%{?dist}
Summary:	Enable or disable the 1PPS input on Solar Flare cards.

Group:		Applications/System
License:	GPLv2
URL:		https://github.com/lukebigum/sfppsctrl
Source0:	%{name}-%{version}.tar.gz

%description
Enable or disable the 1PPS input on Solar Flare cards.

%prep
%setup -q


%build
make


%install
mkdir -p %{buildroot}/usr/sbin/
cp sfppsctrl %{buildroot}/usr/sbin/
mkdir -p %{buildroot}/etc/rc.d/init.d/
cp sfppsctrl.init %{buildroot}/etc/rc.d/init.d/sfppsctrl
mkdir -p %{buildroot}/etc/sysconfig/
cp sfppsctrl.sysconfig %{buildroot}/etc/sysconfig/sfppsctrl

%files
%defattr(0644,root,root,0755)
%config(noreplace) /etc/sysconfig/sfppsctrl
%defattr(0755,root,root,0755)
/usr/sbin/sfppsctrl
/etc/rc.d/init.d/sfppsctrl


%changelog
* Tue Oct 17 2017 Luke Bigum <luke.bigum@lmax.com> - 1.0-1
- Initial Release
