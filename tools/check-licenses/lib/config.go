// Copyright 2020 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package lib

import (
	"encoding/json"
	"io/ioutil"
	"os"
)

// Config values are populated from the the json file at the default or user-specified path
type Config struct {
	FilesRegex          []string        `json:"filesRegex,omitempty"`
	SkipDirsRegex       []string        `json:"skipDirsRegex"`
	SkipFilesRegex      []string        `json:"skipFilesRegex"`
	TextExtensions      map[string]bool `json:"textExtensions"`
	MaxReadSize         int             `json:"maxReadSize"`
	SeparatorWidth      int             `json:"separatorWidth"`
	OutputFilePrefix    string          `json:"outputFilePrefix"`
	OutputFileExtension string          `json:"outputFileExtension"`
	Product             string          `json:"product"`
	SingleLicenseFiles  []string        `json:"singleLicenseFiles"`
	LicensePatternDir   string          `json:"licensePatternDir"`
	BaseDir             string          `json:"baseDir"`
	Target              string          `json:"target"`
	LogLevel            string          `json:"logLevel"`
}

// Init populates Config object with values found in the json config file
func (config *Config) Init(configJson *string) error {
	jsonFile, err := os.Open(*configJson)
	defer jsonFile.Close()
	if err != nil {
		return err
	}
	byteValue, err := ioutil.ReadAll(jsonFile)
	if err != nil {
		return err
	}
	if err = json.Unmarshal(byteValue, &config); err != nil {
		return err
	}
	return nil
}
