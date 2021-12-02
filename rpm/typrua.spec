# Licence as for the package source

Name:               typrua
Version:            0.1
Release:            1%{?dist}
Summary:            Yet another MarkDown editor, open source!
License:            MulanPSL-2.0
URL:                https://github.com/Reverier-Xu/typrua
BuildArch:	        x86_64 aarch64
Source0:            %{name}-%{version}.tar.gz

BuildRequires:      gcc, cmake, make, qt5-qtbase, qt5-qtbase-devel, qt5-qtwebengine-devel
BuildRequires:      qt5-qtsvg-devel, 

Requires:           qt5-qtbase >= 5.9, qt5-qtwebengine >= 5.9, qt5-qtsvg >= 5.9
Requires:           qt5-qtwebchannel, qt5-qttools, qt5-quickcontrols, qt5-quickcontrols2

%description
Yet another MarkDown editor, open source!

%prep
%setup -q

%build
%{__mkdir_p} build
pushd build || exit 1
cmake -DCMAKE_BUILD_TYPE=Debug ..
%make_build

%install
%{__mkdir_p} %{buildroot}%{_bindir}/
# %%{__mkdir_p} %{buildroot}%{_datadir}/applications/

install -m 755 build/bin/TypRua %{buildroot}%{_bindir}/

# install -m 644 ./TypRua.desktop %{buildroot}%{_datadir}/applications/

%files
%{_bindir}/TypRua
# %%{_datadir}/applications/TypRua.desktop
%doc README.md
%license LICENSE

%changelog
* Thr Dec 2 2021 Li Jingwei <lijingwei@uniontech.com> - 1.0-1
- First try at an RPM